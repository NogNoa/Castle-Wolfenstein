#include "cw.h"
#include "files.h"
#include "game_f~1.h"

typedef byte room[0x10];
typedef room floor[0x8];

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
    room * flr;
    byte * rm;
    byte al, spk;
    for (pg = 1; pg < 0x3f; ++pg)
    {   flr = (room *) (file_buffer + PAGE_SZ*pg + PAGE_SZ/2);
        parity = 0;
        for (j=0; j < 8;++j)
        {   rm = flr[j];
            if (rm[0] & 0xf0 == 0x10)
            {   spk = SpkRng();
                if (10 < (spk & 15)) {spk -= 6;}
                rm[2] = 0;
                rm[7] = spk & 15;
                rm[6] = 0;
                rm[0xc] = 0;
                rm[9] = (byte) SpkRng();
                spk = (byte)SpkRng();
                rm[8] = (spk < 0xd0) ? 0 :
                (spk < 0xf8) ? 1 : 2; 
                if (1 < ++parity) 
                {   parity = 0;
                    if (SpkRng() < rank_index / 2)
                    {   rm[6] = 1;
                        rm[0] = 0x20;
                    }
                }
            }
        }
    }
}

void f45e9(void)
{
    room * flr;
    byte * rm;
    byte spk, nibble_j, carry_over, j;
    int pg, i;
    carry_over = 0xf; 
    j = 0;
    for (pg = 1; pg < 0x3f; pg = pg + 1) 
    {   flr = (room *) (file_buffer + PAGE_SZ*pg + PAGE_SZ/2);
        for (i = 0; i <= 0x7; i = i + 0x1) 
        {   rm = flr[i];
            if ((rm[0] & 0xf0) == 0x30) 
            { /* at first the nibble goes up to f
                but then it's 0 twice in a row instead*/
                nibble_j = j & 0xf;
                if (nibble_j == 0xf) 
                {   nibble_j = carry_over;
                    carry_over = 0;
                }
                rm[2] = nibble_j;
                spk = (byte) SpkRng();
                f4910(spk);
                rm[4] = spk;
                spk = (byte) SpkRng();
                rm[3] = spk;
                rm[7] = 0;
                j = j + 1;
            }
            else if ((rm[0] & 0xf0) == 0x50) 
            {   rm[3] = 1;}  
        }
    }
    return;
}

void __cdecl16near FUN_1000_46c2(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  byte k;
  int pg;
  int i;
  int j;
  
  for (pg = 2; pg < 0xb; pg = pg + 1) {
    iVar2 = pg * 0x100 + 0x33d;
    iVar3 = pg * 0x100 + 0x353d;
    for (i = 0; i < 0x71; i = i + 0x10) {
      bVar1 = *(byte *)(iVar2 + i) & 0xf0;
      if ((bVar1 == 0x10) || (bVar1 == 0x20)) {
        for (j = 0; j < 0x71; j = j + 0x10) {
          pbVar5 = (byte *)(iVar3 + j);
          k = 0;
          if ((*pbVar5 & 0xf0) == 0) {
            *(byte *)(iVar2 + i + 1) = pbVar5[1];
            while( true ) {
              uVar4 = (uint)k;
              if (uVar4 != 0xf && 0xe < k) break;
              k = k + 1;
              *(undefined1 *)(iVar3 + j + uVar4) = *(undefined1 *)(iVar2 + i + uVar4);
            }
            *(undefined1 *)(iVar2 + i) = 0;
            j = 0x70;
            i = 0x70;
          }
        }
      }
    }
  }
  return;
}