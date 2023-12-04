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
    
def split_string_after_phone_number(input_string):
    pattern = r'(\b\d{10}\b)(.*)'  # Biểu thức chính quy để tìm số điện thoại có 10 chữ số liên tiếp và sau đó là phần còn lại
    match = re.search(pattern, input_string)

    if match:
        text_after_phone_number = match.group(2).strip()  # Lấy phần text sau số điện thoại
        if text_after_phone_number.startswith('rằng '):
            text_after_phone_number = text_after_phone_number[5:]  # Xóa 'rằng ' nếu chuỗi bắt đầu với 'rằng '
        elif text_after_phone_number.startswith('là '):
            text_after_phone_number = text_after_phone_number[3:]  # Xóa 'là ' nếu chuỗi bắt đầu với 'là '
        return text_after_phone_number
    else:
        return None

def get_text(input_string):
    text_after_phone = split_string_after_phone_number(input_string)
    if text_after_phone:
        print(text_after_phone)
    else:
        print("None")