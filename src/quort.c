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
    int pg, parity, j;
    byte fb_midpg[8][0x10];
    byte al, spk;
    for (pg = 1; pg < 0x3f; ++pg)
    {   fb_midpg = file_buffer + PAGE_SZ*pg + PAGE_SZ/2;
        parity = 0;
        for (j=0; j < 8;++j;)
        {   if (fb_midpg[j][0] & 0xf0 == 0x10)
            {
                spk = SpkRng();
                if (10 < (spk & 15)) {spk -= 6;}
                fb_midpg[j][2] = 0;
                fb_midpg[j][7] = spk & 15;
                fb_midpg[j][6] = 0;
                fb_midpg[j][0xc] = 0;
                fb_midpg[j][9] = (byte) SpkRng();
                spk = (byte)SpkRng();
                fb_midpg[j][8] = (spk < 0xd0) ? 0 :
                (spk < 0xf8) ? 1 : 2; 
                if (1 < ++parity) 
                {   parity = 0;
                    if (SpkRng() < rank_index / 2)
                    {   fb_midpg[j][6] = 1;
                        fb_midpg[j][0] = 0x20;
                    }
                }
            }
        }
    }
}