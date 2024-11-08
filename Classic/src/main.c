#include "cw.h"
#include "doscall.h"
#include "video.h"
#include "conio.h"
#include "anti_debug.h"
#include "memory.h"
#include "STDLIB.H"

int sum_5fd6;
int arr_5fd6[36];

void main()
{
    setVideoMode(PXL_CLR_LO);
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(2,2));
    cputs("072684");
    sum_5fd6 = sum(arr_5fd6, 36);
    isPcJr();
    if (inhibitInterrupts() < 0) {_exit(-1);}
    setup_memory();
}
