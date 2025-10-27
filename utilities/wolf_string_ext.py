import CGA
import os

os.chdir("utilities")

DATA_SEGMENT_in_FILE = 0xA470

strings_offset = 0x907d
STRINGS_END = 0x9164

with open("../bin/WOLF.CHR", "rb") as file:
    font = file.read()
font = CGA.get_1bit_font(font)

with open("./resources/CW.exe", "rb") as file:
    file.seek(strings_offset + DATA_SEGMENT_in_FILE)
    scroll = file.read(STRINGS_END - strings_offset)

while scroll:
    if strings_offset in (0x90d3, 0x90d4):
        string, scroll = scroll[:1], scroll[1:]
    elif strings_offset == 0x9124:
        string, scroll = scroll[:2], scroll[2:]
    else:
        string, scroll = scroll.split(b'\0',1)
    string = CGA.draw_w_costume_font(string, font)
    string.save("../Media/%x.png" % strings_offset)
    scroll = scroll.lstrip(b'\0')
    strings_offset = STRINGS_END - len(scroll)
