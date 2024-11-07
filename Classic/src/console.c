#include "cw.h"
#include "video.h"
#include "conio.h"

extern bool pcjr; 

void
put_2_lines(line0, line1)
char *line0, *line1;
{   
    if (pcjr) {setVideoMode(TXT_GREY_WD);}
    else {setVideoMode(TXT_GREY_THN);}
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(4,1));
    cputs(line0);
    cputs(line1);
}
