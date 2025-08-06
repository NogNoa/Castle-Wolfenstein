#include "cw.h"
#include "game_files.h"
#include "files.h"

long timer_count;
byte carousel_count;

byte f03a1(byte ah)
{   
    byte al, cf0, cf1,;
    int l7712, l7714, b;
    al = (isDemo) ? *(++GfxFileP) : (byte) timer_count;
    cf0 = al & 1;
    cf1 = l7712 & 1;
    l7712 >>= 1;
    l7712 |= cf0 << 0xf;
    cf0 = l7714 & 1;
    l7714 >>= 1;
    l7714 |= cf1 << 0xf;
    cf1 = l7714 & 1;
    l7714 = (((int) ah << 8) | al) ^ ((l7714 >> 1) | (cf0 << 0xf));
    al = (byte) l7714;
    if (al < carousel_count)
        {pause_resume_sound();}
    return al;
}