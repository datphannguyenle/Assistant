import re

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

input_string = "nhắn vào số 0912345678 là tôi đang trên đường tới"

text_after_phone = split_string_after_phone_number(input_string)
if text_after_phone:
    print("Chuỗi sau số điện thoại:")
    print(text_after_phone)
else:
    print("Không tìm thấy số điện thoại trong chuỗi.")
