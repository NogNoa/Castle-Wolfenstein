#include "cw.h"
#include "files.h"

f4426(void)
{
    int spi,i, b;
    byte *lc, *la;
    byte spk, temp;
    for (spi=1; spi <= 60; ++spi)
    {   do
        {   spk = (byte) SPK03A1();
            spk <<= 1;
            if (spi & 1)
            {
                spk ^= 1;
            }
        } while (!spk || 0x3f <= spk || spk == spi );
        lc = spk << 8 + file_buffer;
        la = spi << 8 + file_buffer;
        for(i=0; i < 0x100; ++i)
        {   if (i == 0x49) {i = 0x4e;}
            temp = lc[i];
            lc[i] = la[i];
            la[i] = temp;
        }
    }
}