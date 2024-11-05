#include "cw.h"
#include "ibm.h"

int i5ff9 = 0x1000;
int i5ff0 = 0;

void
del_inst_5ff9(void)
{
    i5ff9 = 0x9090;
}

int goober_function(int p1, void* dest, register byte* si)
{
    int a;
    byte   i;
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