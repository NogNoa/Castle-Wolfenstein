#include "cw.h"
#include "game_files.h"
#include "files.h"

long timer_count;
byte carousel_count;

#define ROR_WORD(X) ((X) >> 1) | (((X) & 1)<< 0xf)

byte f03a1(byte ah)
{   
    byte al;
    int l7712, l7714;
    al = (isDemo) ? *(++GfxFileP) : (byte) timer_count;
    al >>= 1;
    l7712 = ROR_WORD(l7712);
    l7714 = ROR_WORD(l7714);
    l7714 = (((int) ah << 8) | al) ^ ROR_WORD(l7714);
    al = (byte) l7714;
    if (al < carousel_count)
        {pause_resume_sound();}
    return al;
}