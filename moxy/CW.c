#include "cw.h"
#include "memory.h"

byte d7716, d9e8e;
byte *p7717;
int d7712, d7714;
bool b4b3c;

byte speaker_3a1(void)
{
    byte al;
    bool cf, ct;
    int bx;
    if (d7716)
        {al = *(++p7717);}
    else
        {al = SegMemGet((long)0x46c);}
    cf = al & 1;
    al >>= 1;
    ct = d7712 & 1;
    d7712 = (d7712 >> 1) | ((int) cf << 0xf);
    cf = d7714 & 1;
    d7714 = (d7714 >> 1) | ((int) ct << 0xf);
    ct = cf;
    bx = (d7714 >> 1) | ((int) cf << 0xf);
    d7714 = (int) al ^ bx;
    al = (byte) d7714;
    if (d9e8e < al || !b4b3c)
        {out(0x61, in(0x61) & 0xfe ^ 2);}
    return al;
}

void f3d4()
{   
    if (!b4b3c)
        {out(0x61, in(0x61) & 0xfe ^ 2);}
}
