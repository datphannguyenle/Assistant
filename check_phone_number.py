import re

def check_phone_number(input_string):
    pattern = r'\b\d{10}\b'
    phone_number_match = re.search(pattern, input_string)
    
    if phone_number_match is not None:
        phone_number = phone_number_match.group()  # Lấy chuỗi số điện thoại từ đối tượng match
        valid_pattern = r"^(0|84)[3|5|7|8|9]\d{8}$"
        return bool(re.match(valid_pattern, phone_number))
    else:
        return False