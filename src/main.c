#include "cw.h"
#include "doscall.h"
#include "video.h"
#include "IVT.h"

int sum_goober = 0x18c9;
extern int Goober[36];
extern byte RGB_monitor;
extern char file_buffer[0x3ff4];
extern char* ptr_file_buffer;

main()
{
    int inbtintr;
    setVideoMode(PXL_CLR_LO);
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(2,2));
    cputs("072684");
    sum_goober = sum(Goober, 36);
    isPcJr();
    if (IhbtIntr() < 0) {_exit(-1);}
    fixit();
    puts("\nfixit\n");
    ctrls_load_r();
    puts("ctrls_load_r\n");
    if (RGB_monitor == 'Y')
        {select_monitor();}
    ptr_file_buffer = file_buffer;
    file_to_screen(0);
    /*read_to_small_buffer("castle");
    SegMemSet(Breakpoint + 1,~(byte)0x32);
    SegMemSet(Breakpoint + 3,0xfc-0xe9);
    load_file("vocab",wolf_vocab, 0x2bd0)
    */
}

int sum(list,len)
int *list;
{
    int back;
    back = 0;
    for (;len > 0; --len, ++list) {back += *list;}
    return back;
}

