#include "cw.h"
#include "game_files.h"
#include "files.h"

long timer_count;
byte carousel_count;

byte f03a1(byte ah)
{   
    byte al;
    int l7712, l7714, b;
    al = (isDemo) ? *(++GfxFileP) : (byte) timer_count;
    al >>= 1;
    l7712 = ((l7712) >> 1) | (((l7712) & 1)<< 0xf);
    l7714 = ((l7714) >> 1) | (((l7714) & 1)<< 0xf);
    l7714 |= cf1 << 0xf;
    l7714 = (((int) ah << 8) | al) ^ ((l7714 >> 1) | ((l7714) & 1) << 0xf);
    al = (byte) l7714;
    if (al < carousel_count)
        {pause_resume_sound();}
    return al;
}