import re


def check_phone_number(input_string):
    pattern = r"\b\d{3}[\s.-]?\d{3}[\s.-]?\d{4}\b"  # Updated pattern to match phone numbers with optional spaces, dots, or hyphens
    phone_number_match = re.search(pattern, input_string)

    if phone_number_match is not None:
        phone_number = (
            phone_number_match.group()
        )  # Get the phone number string from the match object
        valid_pattern = r"^(0|84)[3|5|7|8|9]\d{8}$"
        return bool(
            re.match(valid_pattern, re.sub(r"[\s.-]", "", phone_number))
        )  # Remove spaces, dots, or hyphens before checking validity
    else:
        return False


def split_string_after_phone_number(input_string):
    pattern = r"(\b\d{3}[\s.-]?\d{3}[\s.-]?\d{4}\b)(.*)"  # Updated pattern to capture phone numbers with optional spaces, dots, or hyphens
    match = re.search(pattern, input_string)

    if match:
        text_after_phone_number = match.group(
            2
        ).strip()  # Get the text after the phone number
        if text_after_phone_number.startswith("rằng "):
            text_after_phone_number = text_after_phone_number[
                5:
            ]  # Remove 'rằng ' if the string starts with 'rằng '
        elif text_after_phone_number.startswith("là "):
            text_after_phone_number = text_after_phone_number[
                3:
            ]  # Remove 'là ' if the string starts with 'là '
        return text_after_phone_number
    else:
        return None


def get_text(input_string):
    text_after_phone = split_string_after_phone_number(input_string)
    if text_after_phone:
        print(text_after_phone)
    else:
        print("None")
