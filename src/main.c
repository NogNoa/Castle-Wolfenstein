#include "cw.h"
#include "doscall.h"
#include "video.h"
#include "IVT.h"
#include "memory.h"

#define VOCAB_FSIZE 0x2bd0
#define CHR_FSIZE 0x400

int sum_goober = 0x18c9;
extern int Goober[36];
extern char file_buffer[0x3ff4];
extern char* ptr_file_buffer;
byte RGB_monitor;
bool make_sound;
byte wolf_vocab[VOCAB_FSIZE];
byte b77e[3];

byte wolf_font[CHR_FSIZE];

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
    p_ld_pg_b("castle", 0x100);
    SegMemSet(Breakpoint + 1,~(byte)0x32);
    SegMemSet(Breakpoint + 3,0xfc-0xe9);
    load_file("vocab",wolf_vocab, VOCAB_FSIZE);
    b77e = {0, 0, 0};
    if (sum(Goober, 36) != sum_goober + wolf_vocab) {_exit(-1);}
    load_file("wolf.chr", wolf_font, CHR_FSIZE);
    if (sum(Goober, 36) != sum_goober + wolf_font) {_exit(-1);}
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

