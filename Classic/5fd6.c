#include "cw.h"
#include "ibm.h"

int i5ff9 = 0x1000;

void
del_inst_5ff9(void)
{
    i5ff9 = 0x9090;
}

int f5fd6(int p1, void* p2)
{
    int b, a;
    byte   i;
    byte * si;
    int i5ff0 = 0;
    i5ff0 = b = p2;
    switch(i5ff9)
    {case 0x1000:
        *(si + b) = *default_drive;
        break;
    case 0x9090:
        break;
    case 0x200:
        *(si + b) = 1;
        break;
    }
    a = 0x200;
    i5ff9 = a;
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