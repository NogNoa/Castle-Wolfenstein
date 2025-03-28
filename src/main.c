#include "cw.h"
#include "doscall.h"
#include "video.h"
#include "IVT.h"
#include "memory.h"
#include "files.h"
#include "config.h"
#include "game_f~1.h"

int sum_goober = 0x18c9;
extern int Goober[36];
byte RGB_monitor;
bool make_sound;
byte wolf_vocab[VOCAB_FSIZE];
byte b77e[3];

byte wolf_font[CHR_FSIZE];
bool b284 = false;

main()
{
    int inbtintr, l1a, l18, goob0, goob1;
    byte *lpage_a;
    struct cs_pg_t *lcastle_pg;
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
    ld_castle_page_w_ptr("castle", PAGE_SZ);
    SegMemSet(Breakpoint + 1,~(byte)0x32);
    SegMemSet(Breakpoint + 3,0xfc-0xe9);
    load_file("vocab",wolf_vocab, VOCAB_FSIZE);
    b77e[0] = b77e[1] = b77e[2] = 0;
    puts("sum goober wolf vocab");
    printf("%x != %x", sum(Goober, 36), sum_goober + wolf_vocab); /*d521 != B6*/
    /* if ((goob0=) != (goob1 =)) {_exit(-1);}*/
    puts("load file wolf.chr");
    load_file("wolf.chr", wolf_font, CHR_FSIZE);
    puts("sum goober wolf font");
    if (sum(Goober, 36) != sum_goober + wolf_font) {_exit(-1);}
    puts("RdSysFnt");
    RdSysFnt(wolf_font);
    puts("presser to screen");
    file_to_screen(1);
    puts("wait_to_return");
    if (wait_to_return()) /* play demo if the return key isn't pressed in time*/
        {load_demo();}
    b284 = false;
    l1a = 0x8000;
    l18 = 0x8002;
    lpage_a = pg_a;
    lcastle_pg = &castl_pg;
    is_cstle_stt_60();
    if (!isDemo)
        {   rank_print();

        }
    /**/
}

byte save_status;
extern byte rank_index;

is_cstle_stt_60()
{   
    save_status = (castl_pg.save_status == 0x60) ?
                  0xff : 
                  castl_pg.save_status;
    controller = DEV_undefined; 
    rank_index = rank_calculate();
}

int sum(list,len)
int *list;
{
    int back;
    back = 0;
    for (;len > 0; --len, ++list) {back += *list;}
    return back;
}

