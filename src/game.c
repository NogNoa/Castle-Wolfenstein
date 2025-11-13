#include "cw.h"
#include "init.h"
#include "video.h"

extern para_ind para_2ac;

void try_open(void)
{
    clear_status_bar();
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl((23), (14)));
    if ((cstl_pg.keys & rm_pg.rm80[para_2ac -1][2]) == rm_pg.rm80[para_2ac -1][2])
    {
        PositCPuts("It\'s open!", 23, 15);
        /*f313b();*/
    }
    else
        {cputs("Still locked!");}
    cstl_pg.is_looting = false;
}

void clear_status_bar(void)
{
    PositCPuts("                                        ", 23, 1);
    PositCPuts("          ", 24, 1);
}