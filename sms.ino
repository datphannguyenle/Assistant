#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

static const int RXPin = 17, TXPin = 16;
static const uint32_t GPSBaud = 9600;

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

// For stats that happen every 5 seconds
unsigned long last = 0UL;

// Threshold speed in km/h
int thresholdSpeed = 70;

// Define the maximum number of positions to store
const int maxPositions = 100;

// Define a flag to track the proximity to the school, home
bool nearSchool = false;
bool nearHome = false;
static const double SCHOOL_LAT = 11.08024095444668, SCHOOL_LON = 107.69359356483338;
static const double HOME_LAT = 11.081387088090779, HOME_LON = 107.69317036965914;

// Create an array to store positions
struct Position {
  uint8_t day;
  uint8_t month;
  uint16_t year;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  float latitude;
  float longitude;
} positions[maxPositions];
int positionIndex = 0;

SoftwareSerial mySerial(18, 19); //SIM800L Tx & Rx is connected
String s = "";
String phoneNumberfixed = "+84973297567";

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);

  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();

  mySerial.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
  updateSerial();
}

void loop()
{
  // Dispatch incoming characters
  while (ss.available() > 0)
    gps.encode(ss.read());

  if (gps.location.isUpdated())
  {
    // Store the position
    positions[positionIndex].day = gps.date.day();
    positions[positionIndex].month = gps.date.month();
    positions[positionIndex].year = gps.date.year();
    positions[positionIndex].hour = gps.time.hour();
    positions[positionIndex].minute = gps.time.minute();
    positions[positionIndex].second = gps.time.second();
    positions[positionIndex].latitude = gps.location.lat();
    positions[positionIndex].longitude = gps.location.lng() ;

    // Increment the position index and wrap back to 0 if needed
    positionIndex = (positionIndex + 1) % maxPositions;
    Serial.println(gps.location.lat(), 15);
    Serial.println(gps.location.lng(), 15);
  }

  else if (gps.speed.isUpdated())
  {
    Serial.print(F("SPEED      km/h="));
    Serial.println(gps.speed.kmph());
    if (gps.speed.kmph() > thresholdSpeed)
    {
      // Print warning message along with current location and speed
      Serial.print("WARNING: Speed exceeds ");
      Serial.print(thresholdSpeed);
      Serial.print(" km/h! Current location: ");
      Serial.print(gps.location.lat(), 6);
      Serial.print(", ");
      Serial.print(gps.location.lng(), 6);
      Serial.print(". Current speed: ");
      Serial.print(gps.speed.kmph());
      Serial.println(" km/h");
    }
  }

  else if (millis() - last > 5000)
  {
    Serial.println();

    if (gps.location.isValid())
    {
      double distanceToSchool = TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(), SCHOOL_LAT, SCHOOL_LON);

      // Check if you are 500m from the school
      if (distanceToSchool / 1000 <= 0.5)
      {
        // If not already near the school, announce that you have arrived at the school
        if (!nearSchool)
        {
          sendMess("Hoc sinh da den truong", "+84973297567");
          Serial.println("Hoc sinh da den truong");
          nearSchool = true; // Set the flag to true to indicate nearness to the school
        }
      }
      else
      {
        // If already near the school, announce that you are leaving the school
        if (nearSchool)
        {
          sendMess("Hoc sinh da roi khoi truong", "+84973297567");
          Serial.println("Hoc sinh da roi khoi truong");
          nearSchool = false; // Set the flag to false to indicate leaving the school
        }
      }

      double distanceToHome = TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(), HOME_LAT, HOME_LON);

      // Check if you are 500m from the home
      if (distanceToHome / 1000 <= 0.5)
      {
        // If not already near the home, announce that you have arrived at the home
        if (!nearHome)
        {
          sendMess("Hoc sinh da ve nha", "+84973297567");
          Serial.println("Hoc sinh da ve nha");
          nearHome = true; // Set the flag to true to indicate nearness to the home
        }
      }
      else
      {
        // If already near the home, announce that you are leaving the home
        if (nearHome)
        {
          sendMess("Hoc sinh da roi khoi nha", "+84973297567");
          Serial.println("Hoc sinh da roi khoi nha");
          nearHome = false; // Set the flag to false to indicate leaving the home
        }
      }
    }

    if (gps.charsProcessed() < 10)
      Serial.println(F("WARNING: No GPS data.  Check wiring."));

    last = millis();
    Serial.println();
    updateSerial();
    Serial.println(s);
    if (s != " " && s != "\n" && s != "\r")
    {
      int firstQuotePos = s.indexOf("+84");
      int secondQuotePos = s.indexOf('\"', firstQuotePos + 1);
      String phoneNumber = s.substring(firstQuotePos, secondQuotePos);
      Serial.println(phoneNumber);
      if (phoneNumber == phoneNumberfixed)
      {
        String message = "Vi tri hien tai la https://www.google.com/maps?q=";
        message += String(gps.location.lat(), 15);
        message += ",";
        message += String(gps.location.lng(), 15);
        message += " | Toc do hien tai la ";
        message += String(gps.speed.kmph());
        message += " km/h";
        sendMess(message, "+84973297567");
      }
      phoneNumber = "";
    }
    s = "";
  }
}

void sendMess(String content, String phoneNumber) {
  mySerial.print("AT+CMGS=\"");
  mySerial.print(phoneNumber);
  mySerial.println("\"");
  updateSerial();
  mySerial.print(content);
  updateSerial();
  mySerial.write(26);
}

void updateSerial() {
  delay(500);
  while (Serial.available()) {
    mySerial.write(Serial.read()); // Forward what Serial received to Software Serial Port
  }
  while (mySerial.available()) {
    char c = mySerial.read(); // Read character from Software Serial
    if (c != ' ' && c != '\n' && c != '\r') { // Check if character is not space, newline, or carriage return
      s += c; // Append character to string
    }
  }
}
