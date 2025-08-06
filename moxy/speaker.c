#include "cw.h"
#include "game_files.h"
#include "files.h"

long timer_count;
int carousel_count;

byte f03a1(byte ah)
{   
    byte al, cf0, cf1,;
    int l7712, l7714, b, a;
    al = (isDemo) ? *(++GfxFileP) : (byte) timer_count;
    cf0 = al & 1;
    cf1 = l7712 & 1;
    l7712 >>= 1;
    l7712 |= cf0 << 7;
    l7714 >>= 1;
    l7714 |= cf1 << 7;
    b = l7714;
    b >>= 1;
    a = ((int) ah << 8) | al;
    a ^= b;
    l7714 = a;
    ah = 0;
    if (al < carousel_count)
        {pause_resume_sound();}
    return (byte) a;
}