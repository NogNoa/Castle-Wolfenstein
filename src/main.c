#include "cw.h"
#include "doscall.h"
#include "video.h"
#include "IVT.h"
#include "memory.h"
#include "files.h"

int sum_goober = 0x18c9;
extern int Goober[36];
byte RGB_monitor;
bool make_sound;
byte wolf_vocab[VOCAB_FSIZE];
byte b77e[3];

byte wolf_font[CHR_FSIZE];
bool b236 = false;

main()
{
    int inbtintr;
    setVideoMode(PxlClrLo);
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(2,2));
    cputs("072684");
    sum_goober = sum(Goober, 36);
    isPcJr();
    if (IhbtIntr() < 0) {_exit(-1);}
    fixit();
    ctrls_load_r();
    if (RGB_monitor == 'Y')
        {select_monitor();}
    outer_loop:
    ptr_file_buffer = file_buffer;
    file_to_screen(0);
    ld_castle_page_w_ptr("castle", 0x100);
    SegMemSet(Breakpoint + 1,~(byte)0x32);
    SegMemSet(Breakpoint + 3,0xfc-0xe9);
    load_file("vocab",wolf_vocab, VOCAB_FSIZE);
    b77e[0] = b77e[1] = b77e[2] = 0;
    if (sum(Goober, 36) != sum_goober + wolf_vocab) {_exit(-1);}
    load_file("wolf.chr", wolf_font, CHR_FSIZE);
    if (sum(Goober, 36) != sum_goober + wolf_font) {_exit(-1);}
    RdSysFnt(wolf_font);
    file_to_screen(1);
    if (wait_to_return())
        {load_demo();}
    b236 = false;
    int l1a = 0x8000;
    int l18 = 0x8002;
    void *lpage_a = pg_a;
    void *lcastle_pg = castl_pg;
    /**/
}

int sum(list,len)
int *list;
{
    int back;
    back = 0;
    for (;len > 0; --len, ++list) {back += *list;}
    return back;
}

