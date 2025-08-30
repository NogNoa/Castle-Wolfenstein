#include "cw.h"
#include "files.h"
#include "game_f~1.h"

typedef byte paragraph[0x10];
typedef paragraph floor[0x8];

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
    paragraph * flr;
    byte * rm;
    byte al, spk;
    for (pg = 1; pg < 0x3f; ++pg)
    {   flr = (paragraph *) (file_buffer + PAGE_SZ*pg + PAGE_SZ/2);
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
    paragraph * flr;
    byte * rm;
    byte spk, nibble_j, carry_over, j;
    int pg, i;
    carry_over = 0xf; 
    j = 0;
    for (pg = 1; pg < 0x3f; pg = pg + 1) 
    {   flr = (paragraph *) (file_buffer + PAGE_SZ*pg + PAGE_SZ/2);
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
                wait_x10(spk);
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

void f46c2(void)

{
    byte nib_hi;
    paragraph * flr0;
    paragraph * flr1;
    byte k;
    int pg;
    int i;
    int j;
    
    for (pg = 2; pg < 0xb; ++pg) 
    {   flr0 = (paragraph *)  (file_buffer + PAGE_SZ* pg         + PAGE_SZ/2);
        flr1 = (paragraph *)  (file_buffer + PAGE_SZ*(pg + 0x20) + PAGE_SZ/2);
        for (i = 0; i <= 7; ++i) 
        {   nib_hi = flr0[i][0] & 0xf0;
            if ((nib_hi == 0x10) || (nib_hi == 0x20)) 
            {   for (j = 0; j <= 7; ++j) 
                {   k = 0;
                    if ((flr1[j][0] & 0xf0) == 0) 
                    {   flr0[i][1] = flr1[j][1];
                        for(k=0; 0x10 > k;++k) 
                        {   flr1[j][k] = flr0[i][k];}
                        flr0[i][0] = 0;
                        j = 7;
                        i = 7;
                    }
                }
            }
        }
    }
}

byte pga_search(call)
byte call;
{
  byte checked;
  byte ref;
  char i;
  byte j;
  
  i = 0x3f;
  do {
    do {
      ref = ++call & 0x3f;
    } while (rm_pg[ref] & 0x38);
    j = 1;
    checked = rm_pg_70[j*0x10 + 1];
    while (j < 9 && checked != ref &&
            (checked + 8 != ref) && (checked - 8 != ref)) {
      ++j;
    }
    --i;
  } while ((j < 9) && i);
  return ref;
}

void cstl_reset(void)

{
  int k;
  int par;
  int i;
  int j;
  
  cstl_pg.s_43 = pga_search((byte)SpkRng());
  for (par = 1; par < 9; par = par + 1) {
    k = par * 0x10;
    if (rm_pg_70[k] == 0x20) {
      rm_pg_70[k] = 0x10;
      rm_pg_70[k + 6] = 0;
    }
  }
  cstl_pg.pgaind = 1;
  cstl_pg.s_4b = (byte)SpkRng() | 0x80;
  cstl_pg.bulletCount = 10;
  cstl_pg.granadeCount = 0;
  cstl_pg.s_4c = 0;
  cstl_pg.unlktm = 0;
  cstl_pg.s_52 = 0;
  cstl_pg.save_status = 0;
  cstl_pg.s_41 = 0;
  cstl_pg.s_42 = 0;
  cstl_pg.uniform = 0;
  cstl_pg.vest = 0;
  cstl_pg.s_59 = 0;
  for (i = 0; i < 4; i = i + 1) {
    for (j = 0; j < 4; j = j + 1) {
      cstl_pg.table_4_4[i][j] = 0;
    }
  }
  return;
}

void wait_x10(time)
{
    int i;
    for (i = time * 10; i > 0; --i) {}
}