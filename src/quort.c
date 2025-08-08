#include "cw.h"
#include "files.h"

f4426(void)
{
    word spi, i;
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
        } while (0 == spk || 0x3f <= spk || spk == spi );
        lc = file_buffer + ((word) spk << 8);
        la = file_buffer + (spi << 8);
        for(i=0; i < 0x100; ++i)
        {   if (i == 0x49) {i = 0x4e;}
            temp = lc[i];
            lc[i] = la[i];
            la[i] = temp;
        }
    }
}