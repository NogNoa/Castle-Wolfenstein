#include "cw.h"
#include "video.h"

extern bool pcjr; 

int row_coll(byte row, byte coll)
{   
    return (row - 1) << 8 | (coll - 1);
}

/*void*/ 
put_2_lines(line0, line1)
char *line0, *line1;
{   
    if (pcjr) {set_video_mode(TXT_GREY_WD);}
    else {set_video_mode(TXT_GREY_THN);}
    BiosVideo(SET_CURSOR_POSITION, 0, 0, row_coll(4,1));
    cputs(line0);
    cputs(line1);
}