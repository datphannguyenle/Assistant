import re

def is_valid_phone_number(phone_number):
    pattern = r"^(0|84)[3|5|7|8|9]\d{8}$"
    return bool(re.match(pattern, phone_number))

def extract_phone_number(input_string):
    pattern = r'\b\d{10}\b'
    phone_numbers = re.findall(pattern, input_string)
    return phone_numbers

input_string = "gọi cho tôi số 0912452788 đi"

phone_numbers = extract_phone_number(input_string)

if phone_numbers:
    for phone_number in phone_numbers:
        if is_valid_phone_number(phone_number):
            print("Số điện thoại được tìm thấy trong chuỗi:")
            print(phone_number)
        else:
            print("Số điện thoại trong chuỗi không hợp lệ.")
else:
    print("Không tìm thấy số điện thoại trong chuỗi.")