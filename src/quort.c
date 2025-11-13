#include "cw.h"
#include "files.h"
#include "init.h"

#ifdef __WATCOMC__
#include "drawa.h"
void wait_x10(int time);
#endif

typedef byte paragraph[0x10];
typedef paragraph amud[0x8];

void scramble_castle(void)
{
    /* scramble whole pages from the room area
    only even with even and odd with odd
    [1..3C:2] <=> [1..40:2]
    [2..3D:2] <=> [2..39:2]
    */
    word rmj, i;
    page *roomk, *roomj;
    byte rmk, temp;
    for (rmj=1; rmj < 0x3D; ++rmj) /*rmj not in pages 3D..40*/
    {   while (true)
        {   rmk = (byte) SpkRng();
            rmk <<= 1;
            if (rmj & 1) {rmk ^= 1;} /*if rmj odd, so is rmk and v.v*/
            if (0 < rmk && rmk < 0x40 && rmk != rmj) /* find diffrent*/
                {break;}
        }
        roomk = (page *) file_buffer + ((word) rmk << 8);
        roomj = (page *) file_buffer + (rmj << 8);
        for(i=0; i < PAGE_SZ; ++i)
        {   if (i == 0x49) {i = 0x4e;}
            temp = *roomk[i];
            *roomk[i] = *roomj[i];
            *roomj[i] = temp;
        }
    }
}

void f44db(void)
{
    /* swetting up variables in each paragraph 
    in the 2nd half of each page
    */
    int pg, parity, j;
    amud * flr;
    byte * par;
    byte spk;
    for (pg = 1; pg < 0x3f; ++pg)
    {   flr = (amud *) (file_buffer + PAGE_SZ*pg + PAGE_SZ/2);
        parity = 0;
        for (j=0; j < 8;++j)
        {   par = *flr[j];
            if ((par[0] & 0xf0) == 0x10)
            {   spk = SpkRng();
                if (10 < (spk & 0xf)) {spk -= 6;} 
                par[2] = 0;
                par[7] = spk & 0xf;
                par[6] = 0;
                par[0xc] = 0;
                par[9] = (byte) SpkRng();
                spk = (byte)SpkRng();
                par[8] = (spk < 0xd0) ? 0 :
                (spk < 0xf8) ? 1 : 2; 
                if (1 < ++parity) 
                {   parity = 0;
                    if (SpkRng() < rank_index / 2)
                    {   par[6] = 1;
                        par[0] = 0x20;
                    }
                }
            }
        }
    }
}

void f45e9(void)
{
    amud * flr;
    byte * par;
    byte spk, nibble_j, carry_over, j;
    int pg, i;
    carry_over = 0xf; 
    j = 0;
    for (pg = 1; pg < 0x3f; pg = pg + 1) 
    {   flr = (amud *) (file_buffer + PAGE_SZ*pg + PAGE_SZ/2);
        for (i = 0; i < 8; i = i + 0x1) 
        {   par = *flr[i];
            if ((par[0] & 0xf0) == 0x30) 
            { /* at first the nibble goes up to f
                but then it's 0 twice in a row instead*/
                nibble_j = j & 0xf;
                if (nibble_j == 0xf) 
                {   nibble_j = carry_over;
                    carry_over = 0;
                }
                par[2] = nibble_j;
                spk = (byte) SpkRng();
                wait_x10(spk);
                par[4] = spk;
                spk = (byte) SpkRng();
                par[3] = spk;
                par[7] = 0;
                j = j + 1;
            }
            else if ((par[0] & 0xf0) == 0x50) 
            {   par[3] = 1;}  
        }
    }
    return;
}

void f46c2(void)

{
    byte nib_hi;
    amud * flr0;
    amud * flr1;
    char k;
    int pg;
    int i;
    int j;
    
    for (pg = 2; pg < 0xb; ++pg) 
    {   flr0 = (amud *)  (file_buffer + PAGE_SZ* pg         + PAGE_SZ/2);
        flr1 = (amud *)  (file_buffer + PAGE_SZ*(pg + 0x20) + PAGE_SZ/2);
        for (i = 0; i <= 7; ++i) 
        {   nib_hi = *flr0[i][0] & 0xf0;
            if ((nib_hi == 0x10) || (nib_hi == 0x20)) 
            {   for (j = 0; j <= 7; ++j) 
                {   k = 0;
                    if ((*flr1[j][0] & 0xf0) == 0) 
                    {   *flr0[i][1] = *flr1[j][1];
                        for(k=0; 0x10 > k;++k) 
                        {   *flr1[j][k] = *flr0[i][k];}
                        *flr0[i][0] = 0;
                        j = 7;
                        i = 7;
                    }
                }
            }
        }
    }
}

byte fnd_fr_tile(call)
byte call;
{
    byte checked;
    char i, tile, j;
    
    i = 0x3f;
    do {
        do {
            tile = ++call & 0x3f;
        } while (rm_pg.tl_tble[tile] & 0x38);
        j = 1;
        checked = rm_pg.rm80[j -1][1];
        while (j < 9 && 
            checked != tile &&
            (checked + 8 != tile) && 
            (checked - 8 != tile)){++j;}
        --i;
    } while ((j < 9) && i);
    return tile;
}

void cstl_reset(void)

{
    int k;
    int par;
    int i;
    int j;
    
    cstl_pg.tile_pl_rm = fnd_fr_tile((byte)SpkRng());
    for (par = 1; par < 9; par = par + 1) {
        k = par * 0x10;
        if (rm_pg.rm80[par -1][0] == 0x20) {
        rm_pg.rm80[par -1][0] = 0x10;
        rm_pg.rm80[k -1][6] = 0;
        }
    }
    cstl_pg.rm_id = 1;
    cstl_pg.pl_aim = (byte)SpkRng() | 0x80;
    cstl_pg.bulletCount = 10;
    cstl_pg.granadeCount = 0;
    cstl_pg.bonk_timer = 0;
    cstl_pg.act_timer = 0;
    cstl_pg.is_looting = 0;
    cstl_pg.save_status = 0;
    cstl_pg.mov_dir = 0;
    cstl_pg.aim_dir = 0;
    cstl_pg.uniform = 0;
    cstl_pg.vest = 0;
    cstl_pg.keys = 0;
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