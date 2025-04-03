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
byte b77e[3] = {0};

byte wolf_font[CHR_FSIZE];
bool b284 = false;

#ifdef PRODEBUG
uint IhbtIntr();
#endif


main()
{
    int inbtintr, l1a, l18, goob0, goob1;
    byte *lpage_a;
    struct cs_pg_t *lcastle_pg;
    setVideoMode(PxlClrLo);
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(2,2));
    cputs("072684");
    printf("\nsum_goober=%x goober at %x\n", sum_goober, Goober);
    sum_goober = Sum(Goober, 0x24);
    printf("\nsum_goober=%x goober at %x\n", sum_goober, Goober);
    printf("%x %x  %x %x\n", Goober[0xC], Goober[0xD], Goober[0x11], Goober[0x12]);
    /*sum_goober= 0x9022*/
    /*synth sum_goober=CEC3*/
    isPcJr();
    if (IhbtIntr() < 0) {_exit(-1);}
    printf("summingg goober=%x\n", Sum(Goober, 0x24));
    fixit();
    printf("summingg goober=%x\n", Sum(Goober, 0x24));
    ctrls_load_r();
    printf("summingg goober=%x\n", Sum(Goober, 0x24));
    if (RGB_monitor == 'Y')
        {select_monitor();}
    outer_loop:
    ptr_file_buffer = file_buffer;
    /* file_to_screen(0);*/
    ld_castle_page_w_ptr("castle", PAGE_SZ);
    /*SegMemSet(Breakpoint + 1,~(byte)0x32);
    SegMemSet(Breakpoint + 3,0xfc-0xe9);*/
    printf("summingg goober=%x\n", Sum(Goober, 0x24));
    load_file("vocab",wolf_vocab, VOCAB_FSIZE); /*originally wolf_vocab=0x4b3d, synth wolf_vocab=a2*/
    /* somehow doesn't add dest to the value of the sum*/
    printf("sum_goober=%x b77e at %x wolf_vocab=%x\n", sum_goober, b77e, wolf_vocab);
    printf("summingg goober=%x\n", Sum(Goober, 0x24));
    printf("%x %x  %x\n", b77e[0], b77e[1], b77e[2]);
    printf("summingg goober=%x\n", Sum(Goober, 0x24));
    /*b77e[0] = b77e[1] = b77e[2] = 0; /* somehow interfares in the value of the sum*/
    printf("summingg goober=%x\n", Sum(Goober, 0x24));
    printf("%x != %x\n", Sum(Goober, 0x24), sum_goober + wolf_vocab); /*C094 != CF65*/
    /* if ((goob0=) != (goob1 =)) {_exit(-1);}*/
    puts("load file wolf.chr");
    load_file("wolf.chr", wolf_font, CHR_FSIZE);
    puts("sum goober wolf font");
    if (Sum(Goober, 36) != sum_goober + wolf_font) {_exit(-1);}
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

