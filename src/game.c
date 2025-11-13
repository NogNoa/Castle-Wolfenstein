#include "video.h"

void game_try_open(void)
{
    clear_status_bar();
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl((23), (14)));
    bl = rm_pg.rm80[para_2ac -1][2];
    cl = cstl_pg.keys & bl;
    al = rm_pg.rm80[para_2ac -1][2]
}
