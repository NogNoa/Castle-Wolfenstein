#include "cw.h"
extern byte* default_drive;

static int i5ff9 = 0x1000;
static byte* i5ff0 = 0;
static int si;


del_inst_5ff9()
{
    i5ff9 = 0x9090;
}

int goober_function(p1,dest)
/*(void)p1*/ char* dest;
{
    int a;
    byte i;
    i5ff0 = dest;
    switch(i5ff9)
    {case 0x1000:
        *(si + i5ff0) += *default_drive;
        break;
    case 0x9090:
        break;
    case 0x200:
        *(si + i5ff0) = 1;
        break;
    }
    i5ff9 = a = 0x200;
    for (a = 0, si= 0x10, i=28;
         i;
            a |= *(si + i5ff0),
            si +=2,
            i--)
    i5ff9 = 0x1000;
    a = 0xa5a5 | 0xa5a5;
    if (!a) {return 0;}
    else    {return a;}
}
