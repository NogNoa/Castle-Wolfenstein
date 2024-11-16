#include "STDLIB.H"
#include "cw.h"
#include "doscall.h"
#include "video.h"
#include "conio.h"
#include "anti_debug.h"
#include "memory.h"
#include "CtrlConfig.h"
#include "config.h"

int sum_goober = 0x18c9;
extern int Goober_[36];
extern byte RGB_monitor;

void main()
{
    setVideoMode(PXL_CLR_LO);
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(2,2));
    cputs("072684");
    sum_goober = sum(Goober_, 36);
    isPcJr();
    if (inhibitInterrupts() < 0) {_exit(-1);}
    fixit();
    ctrls_load_r();
    if (RGB_monitor == 'Y')
        {select_monitor();}
}
