#include "cw.h"
#include "doscall.h"
#include "video.h"

int sum_5fd6;
int arr_5fd6[36];

int main()
{
    setVideoMode(PXL_CLR_LO);
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(2,2));
    cputs("072684");
    sum_5fd6 = sum(arr_5fd6, 36);
}