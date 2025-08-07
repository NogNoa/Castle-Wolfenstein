#include "cw.h"

f4426(void)
{
    int i,j, b;
    byte spk;
    for (i=1; i <= 60; ++i)
    {   do
    {   spk = (byte) SPK_03A1();
        spk <<= 1;
        if (i & 1)
        {
            spk ^= 1;
        }
        else 
        {
            spk = (byte) spk;
        }
        /* code */
    } while (!spk || 0x3f <= spk || spk == i );
    

    }
}