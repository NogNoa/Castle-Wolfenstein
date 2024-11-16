#include "cw.h"
#include "doscall.h"
#include "video.h"

int sum_goober = 0x18c9;
extern int Goober[36];

main()
{
    setVideoMode(PXL_CLR_LO);
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(2,2));
    cputs("072684");
    sum_goober = sum(Goober, 36);
    isPcJr();
    if (inhibitInterrupts() < 0) {_exit(-1);}
    fixit();
}
