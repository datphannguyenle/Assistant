import requests


def reverse_geocode(latitude, longitude):
    url = f"https://nominatim.openstreetmap.org/reverse?lat={latitude}&lon={longitude}&format=json"

    response = requests.get(url)

    if response.status_code == 200:
        data = response.json()
        display_name = data.get("display_name")
        return display_name
    else:
        print("Failed to make the request.")
        return None


def get_location_info(latitude, longitude):
    address = reverse_geocode(latitude, longitude)
    if address:
        return address
    else:
        return "Không nhận diện được"
