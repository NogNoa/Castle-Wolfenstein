import CGA

DATA_SEGMENT_in_FILE = 0xA470

strings_offset = 0x907d
strings_end = 0x9164

with open("../bin/WOLF.CHR", "rb") as file:
    font = file.read()
font = CGA.get_1bit_font(font)

with open("./resources/CW.exe", "rb") as file:
    file.seek(strings_offset + DATA_SEGMENT_in_FILE)
    scroll = file.read(strings_end - strings_offset)

offset = 0

while scroll:
    scroll.lstrip(b'\0')
    