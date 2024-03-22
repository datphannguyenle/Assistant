import re


def check_phone_number(input_string):
    pattern = (
        r"\b\d{3}\s\d{3}\s\d{4}\b"  # Định dạng số điện thoại cụ thể "097 329 7567"
    )
    phone_number_match = re.search(pattern, input_string)

    if phone_number_match is not None:
        phone_number = (
            phone_number_match.group()
        )  # Lấy chuỗi số điện thoại từ đối tượng match
        valid_pattern = r"^(0|84)[3|5|7|8|9]\d{8}$"
        return bool(
            re.match(valid_pattern, re.sub(r"\s", "", phone_number))
        )  # Loại bỏ khoảng trắng trước khi kiểm tra tính hợp lệ
    else:
        return False


def split_string_after_phone_number(input_string):
    pattern = r"(\b\d{3}\s\d{3}\s\d{4}\b)(.*)"  # Định dạng để nhận diện số điện thoại cụ thể "097 329 7567"
    match = re.search(pattern, input_string)

    if match:
        text_after_phone_number = match.group(
            2
        ).strip()  # Lấy phần text sau số điện thoại
        # Kiểm tra và loại bỏ 'rằng ' hoặc 'là ' nếu chuỗi bắt đầu với 'rằng ' hoặc 'là '
        if text_after_phone_number.startswith("rằng "):
            text_after_phone_number = text_after_phone_number[5:]
        elif text_after_phone_number.startswith("là "):
            text_after_phone_number = text_after_phone_number[3:]
        return text_after_phone_number
    else:
        return None


def get_text(input_string):
    text_after_phone = split_string_after_phone_number(input_string)
    if text_after_phone:
        return text_after_phone
        # print(text_after_phone)
    else:
        print("None")
