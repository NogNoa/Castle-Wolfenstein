#include "cw.h"
#include "files.h"

scramble_castle(void)
{
    word spj, i;
    byte *fb_pgk, *fb_pgj;
    byte spk, temp;
    for (spj=1; spj <= 60; ++spj)
    {   while (true)
        {   spk = (byte) SpkRng();
            spk <<= 1;
            if (spj & 1)
                {spk ^= 1;}
            if (0 < spk && spk < 0x40 && spk != spj)
                {break;}
        }
        fb_pgk = file_buffer + ((word) spk << 8);
        fb_pgj = file_buffer + (spj << 8);
        for(i=0; i < PAGE_SZ; ++i)
        {   if (i == 0x49) {i = 0x4e;}
            temp = fb_pgk[i];
            fb_pgk[i] = fb_pgj[i];
            fb_pgj[i] = temp;
        }
    }
}

f44db(void)
{
    int pg, lc, l4, j, si;
    byte al, spk;
    for (pg = 1; pg < 0x3f; ++pg)
    {   lc = pg*PAGE_SZ + PAGE_SZ/2 + 0x2bd;
        l4 = 0;
        for (j=0; j <= 0x70;j +=0x10;)
        {   if (lc[j] & 0xf0 == 0x10)
            {
                spk = SpkRng();
                if (10 < (spk & 15)) {spk -= 6;}
                lc[j+2] = 0
            }
        }
    }
}