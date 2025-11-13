#include "cw.h"
#include "memory.h"

byte running_demo, carousel_count;
byte *gfx_file_pointer;
int prng0, prng1;
bool speaker_lock;

byte speaker_3a1(void)
{
    byte al;
    bool cf, ct;
    int bx;
    if (running_demo)
        {al = *(++gfx_file_pointer);}
    else
        {al = SegMemGet((long)0x46c);}
    cf = al & 1;
    al >>= 1;
    ct = prng0 & 1;
    prng0 = (prng0 >> 1) | ((int) cf << 0xf);
    cf = prng1 & 1;
    prng1 = (prng1 >> 1) | ((int) ct << 0xf);
    ct = cf;
    bx = (prng1 >> 1) | ((int) cf << 0xf);
    prng1 = (int) al ^ bx;
    al = (byte) prng1;
    if (carousel_count < al || !speaker_lock)
        {out(0x61, in(0x61) & 0xfe ^ 2);}
    return al;
}

void f3d4()
{   
    if (!speaker_lock)
        {out(0x61, in(0x61) & 0xfe ^ 2);}
}
