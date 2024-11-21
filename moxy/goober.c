#include "../src/cw.h"
#include "../src/video.h"
#include "../src/memory.h"

extern byte* default_drive;

static int i5ff9 = 0x1000;
static word* p5ff0 = 0;
static int si;

void
del_inst_5ff9(void)
{
    i5ff9 = 0x9090;
}

extern word* gfx_file_pointer;

void draw_lower_middle(void)
{
    word* dest=0x1424;
    int i, j;
    for (j=0; (word)dest+j <0x1745; j+=0x50)
        for (i=0;i<0x10;++i)
        {   WSegMem_Set(long_ptr(DISPLAY_BUFFER, (word)(dest + i) + j),
                        *(gfx_file_pointer + i));
            WSegMem_Set(long_ptr(DISPLAY_BUFFER, (word)(dest + i) + 0x2000),
                        *(gfx_file_pointer + i + 0x10));
        }
}

int goober_function(int p1, void* dest)
{
    int a;
    byte i;
    (void)p1;
    p5ff0 = dest;
    switch(i5ff9)
    {case 0x1000:
        *(si + p5ff0) += *default_drive;
        break;
    case 0x9090:
        break;
    case 0x200:
        *(si + p5ff0) = 1;
        break;
    }
    i5ff9 = a = 0x200;
    for (a = 0, si= 5, i=28;
         i;
            a |= *(si + p5ff0),
            ++si,
            --i)
    i5ff9 = 0x1000;
    a = 0xa5a5 | 0xa5a5;
    if (!a) {return 0;}
    else    {return a;}
}


