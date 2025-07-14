
#include "cw.h"
#include "video.h"
#include "IVT.h"
#include "memory.h"
#include "files.h"
#include "config.h"
#include "game_f~1.h"


#ifdef __WATCOMC__
#include "conio.h"
#include "anti_debug.h"
#include "sonara.h"
#include "cwa.h"
void is_cstle_stt_60(void);
void rank_print(void);
void start_menu(void);
void reverse_control(void);
#else
extern int Goober[36];
#endif

int sum_goober = 0x18c9;

byte RGB_monitor;
bool make_sound;
byte wolf_vocab[VOCAB_FSIZE];
byte b77e[3] = {0};

byte wolf_font[CHR_FSIZE];
bool b284 = false;

#ifdef PRODEBUG
uint IhbtIntr();
#endif

void
main()
{
    int l1a, l18, stroke;
    byte *lpage_a;
    bool cont;
    struct cs_pg_t *lcastle_pg;
    setVideoMode(PxlClrLo);
    PositCPuts(2,2, "072684");
    sum_goober = Sum(Goober, 0x24);
    isPcJr();
    if (IhbtIntr() < 0) {_exit(-1);}
    fixit();
    r_ctrls_load();
    if (RGB_monitor == 'Y')
        {select_monitor();}
    outer_loop:
    ptr_file_buffer = file_buffer;
    cprintf("setup\n:file_buffer: $%x\nptr_file_buffer: $%x\n",  file_buffer, ptr_file_buffer);
    /* file buffer: $3674 ptr_file_buffer: $3674*/
    file_to_screen(0);
    cprintf("file_to_screen:\nfile_buffer: $%x\nptr_file_buffer: $%x\n",  file_buffer, ptr_file_buffer);
    /* file buffer 36b4 ptr_file_buffer: 0*/
    /* diabling file to screen somehow zeroes ptr_file_buffer - file_buffer from C94A*/
    ld_castle_page_w_ptr("castle", PAGE_SZ);
    SegMemSet(Breakpoint + 1,~(byte)0x32);
    SegMemSet(Breakpoint + 3,0xfc-0xe9);
    load_file("vocab",wolf_vocab, VOCAB_FSIZE);
    load_file("wolf.chr", wolf_font, CHR_FSIZE);
    if (Sum(Goober, 36) != sum_goober + (int) wolf_font) {_exit(-1);}
    RdSysFnt(wolf_font);
    file_to_screen(1);
    if (wait_to_return()) /* play demo if the return key isn't pressed in time*/
        {load_demo();}
    b284 = false;
    l1a = 0x8000;
    l18 = 0x8002;
    lpage_a = pg_a;
    lcastle_pg = &cstl_pg;
    is_cstle_stt_60();
    return 0;
    if (!isDemo)
        {   rank_print();
            PositCPuts(9,8, "What controls do you want ?");
            PositCPuts(11,11, "Press: K for keyboard");
            PositCPuts(13,18, "J for joystick");
            PositCPuts(21,3, "Press Ctrl-N to start a new game");
            PositCPuts(22,3, "Press Ctrl-R to reverse controls");
            PositCPuts(23,3, "Press Ctrl-Q to select monitor type");
            do {
                while (!IsKStrok());
                cont = false;
                stroke = GetStrok();
                switch (stroke)
                {
                case (CTRL('N')):
                    start_menu();
                    break;
                case (CTRL('R')):
                    reverse_control();
                    break;
                case (CTRL('Q')):
                    select_monitor();
                    break;
                case ('K'):
                case ('k'):
                    controller = DEV_keyboard;
                    break;
                case ('J'):
                case ('j'):
                    controller = DEV_joystick;
                    break;
                default:
                    cont = true;
                }
            } while (cont);
        }
    /**/
}

byte save_status;
extern byte rank_index;

void
is_cstle_stt_60(void)
{   
    save_status = (cstl_pg.save_status == 0x60) ?
                  0xff : 
                  cstl_pg.save_status;
    controller = DEV_undefined; 
    rank_index = rank_calculate();
}

