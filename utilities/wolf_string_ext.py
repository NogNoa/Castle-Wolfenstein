import CGA
CGAROM = "utilities/resources/IBM-CGA.rom"

DATA_SEGMENT_in_FILE = 0xA470

strings_offset = 0x907d
strings_end = 0x9164

with open("bin/WOLF.CHR", "rb") as file:
    font = file.read()
font = CGA.get_1bit_font(font)

with open("utilities/resources/CW.exe", "rb") as file:
    file.seek(strings_offset + DATA_SEGMENT_in_FILE)
    scroll = file.read(strings_end - strings_offset)

while scroll:
    scroll.lstrip(b'\0')
    offset = strings_end - len(scroll)
    string, scroll = scroll.split(b'\0',1)
    string = CGA.draw_w_costume_font(string, font)
    string.save("%x.png" % offset)
