#include "cw.h"

char cl;
short si;
extern char ascii_flags[];

void _pfmt(char* format_type)
{
    int local[0x1B];
    char bvar1;
    local[0x13] = -1;
    local[0x12] = 0x20;
    local[0x16] = local[0x11] = local[0x15] = local[0x14] = 0;
    if (*format_type == 0x2d)
    {
        ++format_type;
        local[0x16] = 1;
    }
    local[0] = *format_type;
    bvar1 = ascii_flags[(int)*format_type];
    if (bvar1 & 4 != 0 && local[0] == 0x30)
        {local[0x12] = 0x30;}
    for (;bvar1 & 4 != 0; bvar1 = *(char *)(*format_type + 0xa0b5))
    {   local[0x11] *= 0xa;
        local[0x11] += (*format_type & 0xf);
        ++format_type;
    }
}

