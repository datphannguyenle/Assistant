import requests
import json


def reverse_geocode(api_key, latitude, longitude):
    url = "https://maps.googleapis.com/maps/api/geocode/json"

    params = {"latlng": f"{latitude},{longitude}", "key": api_key}

    response = requests.get(url, params=params)

    if response.status_code == 200:
        data = response.json()
        print(json.dumps(data, indent=2))
        if data["status"] == "OK":
            formatted_address = data["results"][0]["formatted_address"]
            return formatted_address
        else:
            print(f'Error: {data["error_message"]}')
            return None
    else:
        print("Failed to make the request.")
        return None


def get_location_info(latitude, longitude):
    # Thay thế 'YOUR_API_KEY' bằng khóa API của bạn
    api_key = "AIzaSyAUBcnIZIZDBX2wCrbBDMNK_qgSFWJmN2Q"
    address = reverse_geocode(api_key, latitude, longitude)
    # address = reverse_geocode(api_key, 10.852236127729624, 106.77167090390816)
    if address:
        return
        print(f"Formatted Address: {address}")
    else:
        return "Không nhận diện được"
        print("Failed to retrieve the address.")
