#include "cw.h"

f4426(void)
{
    int i,j, b, lc, la;
    byte spk, bl, al;
    for (i=1; i <= 60; ++i)
    {   do
        {   spk = (byte) SPK_03A1();
            spk <<= 1;
            if (i & 1)
            {
                spk ^= 1;
            }
        } while (!spk || 0x3f <= spk || spk == i );
        lc = spk << 8 + 701;
        la = i << 8 + 701;
        for(j=0; j < 0x100; ++j)
        {   if (j == 073) {j = 78}
            bl = lc[j];
            al = la[j];
            lc[j] = al;
            la[j] = bl;
            temp = bl;
        }
    }
}