#include "cw.h"
#include "ibm.h"

bool del_5ff9 = false;

void
del_inst_5ff9(void)
{
    del_5ff9 = true;
}

int f5fd6(int p1, void* p2)
{
    int b;
    byte al, ah, cl, ch, dl, dh;
    byte * si;
    int i5ff0 = 0x10;
    ch = (byte) p1;
    cl = 0x14;
    al = 1;
    ah = 2;
    i5ff0 = p2;
    dl = *default_drive;
    b = 0;
    dh = 0;
    switch(i5ff0)
    {case 0x10:
        *(si + b) = dl;
        al = 0;
        break;
    case 0x2bd:
    
    }
}