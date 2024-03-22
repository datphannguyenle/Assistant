// GPSSpeedManager.h
#include <TinyGPS++.h>

class GPSSpeedManager {
private:
    TinyGPSPlus gps;
    float maxSpeed;
    bool isAtSchool;
    bool isAtHome;

public:
    GPSSpeedManager(float maxSpeedKmh);
    void updateGPSData();
    bool isOverSpeedLimit();
    bool isAtSchoolOrHome();
};

// GPSSpeedManager.cpp
#include "GPSSpeedManager.h"

GPSSpeedManager::GPSSpeedManager(float maxSpeedKmh) {
    maxSpeed = maxSpeedKmh;
}

void GPSSpeedManager::updateGPSData() {
    // Đọc dữ liệu GPS và cập nhật vị trí, tốc độ
    // ...

    // Kiểm tra vị trí hiện tại có phải là trường học hoặc nhà riêng không
    isAtSchool = (distance_to_school < SCHOOL_RADIUS);
    isAtHome = (distance_to_home < HOME_RADIUS);
}

bool GPSSpeedManager::isOverSpeedLimit() {
    return (gps.speed.kmph() > maxSpeed);
}

bool GPSSpeedManager::isAtSchoolOrHome() {
    return (isAtSchool || isAtHome);
}

// SMSManager.h
#include <GSM.h>

class SMSManager {
private:
    GSM gsmAccess;
    String allowedNumbers[MAX_ALLOWED_NUMBERS];

public:
    SMSManager(String allowedNumbersArray[], int numAllowedNumbers);
    bool isAllowedNumber(String number);
    void readAndProcessSMS();
};

// SMSManager.cpp
#include "SMSManager.h"

SMSManager::SMSManager(String allowedNumbersArray[], int numAllowedNumbers) {
    for (int i = 0; i < numAllowedNumbers; i++) {
        allowedNumbers[i] = allowedNumbersArray[i];
    }
}

bool SMSManager::isAllowedNumber(String number) {
    for (int i = 0; i < MAX_ALLOWED_NUMBERS; i++) {
        if (number == allowedNumbers[i]) {
            return true;
        }
    }
    return false;
}

void SMSManager::readAndProcessSMS() {
    // Kết nối với modul GSM
    gsmAccess.begin();

    // Đọc tin nhắn SMS mới
    GSMMessageList messageList = gsmAccess.readSMS();

    for (int i = 0; i < messageList.count(); i++) {
        GSMMessage message = messageList.at(i);
        String senderNumber = message.sender();

        // Kiểm tra số điện thoại gửi tin nhắn có thuộc danh sách cho phép không
        if (isAllowedNumber(senderNumber)) {
            // Xử lý tin nhắn ở đây
            // ...
        }
    }
}

// Main.ino
#include "GPSSpeedManager.h"
#include "SMSManager.h"

// Thông tin vị trí trường học và nhà riêng
const float SCHOOL_LAT = 10.7812919;
const float SCHOOL_LON = 106.6977461;
const float SCHOOL_RADIUS = 0.5; // Bán kính 500m

const float HOME_LAT = 10.8230989;
const float HOME_LON = 106.6296637;
const float HOME_RADIUS = 0.2; // Bán kính 200m

// Danh sách số điện thoại được phép
String allowedNumbers[] = {"+84912345678", "+84987654321"};

GPSSpeedManager gpsManager(60.0); // Tốc độ tối đa 60km/h
SMSManager smsManager(allowedNumbers, 2); // 2 số điện thoại được phép

void setup() {
    Serial.begin(9600);
    // Khởi tạo các module khác...
}

void loop() {
    gpsManager.updateGPSData();

    if (gpsManager.isOverSpeedLimit()) {
        // Xử lý khi vượt quá tốc độ giới hạn
        Serial.println("Warning: Over speed limit!");
    }

    if (gpsManager.isAtSchoolOrHome()) {
        // Xử lý khi tới trường học hoặc về nhà
        Serial.println("You have arrived at school/home.");
    }

    smsManager.readAndProcessSMS();

    // Ngủ đồng hồ để tiết kiệm pin
    delay(5000); // 5 giây
}
