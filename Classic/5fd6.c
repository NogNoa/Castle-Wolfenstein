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
    int b, ax;
    byte al, ah, cl, ch, dl, dh;
    byte * si;
    int i5ff0 = 0;
    ch = (byte) p1;
    cl = 0x14;
    al = 1;
    ah = 2;
    b = p2;
    i5ff0 = b;
    dl = *default_drive;
    b = i5ff0;
    dh = 0;
    switch(i5ff9)
    {case 0x1000:
        *(si + b) = dl;
        break;
    case 0x9090:
        break;
    case 0x200:
        *(si + b) = al;
        break;
    }
    al = 0;
    ax = ah << 8 + al;
    i5ff9 = ax;
    cl = 28; ch = 0;
    ax = 0;
    b = i5ff0;
    si = 0x10;
    while (cl--)
    {   ax  |= *(si + b);
        si += 2;   
    }
    i5ff9 = 0x1000;
    ax = 0xa5a5 | 0xa5a5;
    if (!ax) 
    {   ax = -1;
        return 0;
    }
    else    {return ax;}
}