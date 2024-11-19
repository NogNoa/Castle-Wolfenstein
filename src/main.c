#include "cw.h"
#include "doscall.h"
#include "video.h"

int sum_goober = 0x18c9;
extern int Goober[36];
extern byte RGB_monitor;


main()
{
    setVideoMode(PXL_CLR_LO);
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(2,2));
    cputs("072684");
    sum_goober = sum(Goober, 36);
    isPcJr();
    if (inhibitInterrupts() < 0) {_exit(-1);}
    fixit();
    ctrls_load_r();
    if (RGB_monitor == 'Y')
        {select_monitor();}
}

int sum(list,len)
int *list;
{
    int back;
    back = 0;
    for (;len > 0; --len, ++list) {back += *list;}
    return back;
}

