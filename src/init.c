#include "cw.h"
#include "files.h"
#include "video.h"
#include "game_f~1.h"
#include "config.h"
#include "IVT.h"
#include "memory.h"
#include "FCNTL.H"

#ifdef __WATCOMC__
#include "console.h"
#include "FCNTL.H"
#include "ibm.h"
#include "io1.h"
#include "cwa.h"
#include "peripherals.h"
#include "config.h"
#include "conio.h"
#include "anti_debug.h"
#include "sonara.h"
int Goober(int p1, byte* dest);
void rank_print(void);
void is_cstle_stt_60(void);
void start_menu(void);
void reverse_control(void);
#else
extern int Goober(); /*int[36]*/
#endif

struct cs_pg_t cstl_pg;
word dmodt_offset, dminpind;
byte rank_index;
byte file_buffer[FBUF_SIZE];
byte wolf_font[CHR_FSIZE];
bool isDemo = false;
byte RGB_monitor;
bool make_sound;
byte wolf_vocab[VOCAB_FSIZE];
word error_encountered;

int sum_goober = 0x18c9;
byte b77e[3] = {0};
bool b284, b4ac0;
byte *pdmodt;

byte* pg0_file_buffer = file_buffer;
bool b2aa;

extern bool joyCunfag;
extern int prng0, prng1;
extern int cstl_load_var;
extern word error_encountered, dmodt_offset, dminpind;

inline int checked_open(fn, flags)
string fn;
int flags;
{   int fildsc;
    fildsc = open(fn, flags);
    if (fildsc < 0) 
    {   put_2_strings("Cannot open ", fn);
        _exit(-1);
    }
    return fildsc;
}

int cstl_load_var;
/*
padded byte
==  0 -> resume  
 < 80 -> load   castle
>= 80 -> create castle
*/


#ifdef PRODEBUG
uint IhbtIntr();
#endif

void
main()
{
    int l1a, l18, stroke, i;
    byte *lroom_pg;
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
    file_to_screen(0);
    ld_castle_page_w_ptr("castle", PAGE_SZ);
    SegMemSet(Breakpoint + 1,~(byte)0x32);
    SegMemSet(Breakpoint + 3,0xfc-0xe9);
    load_file("vocab",wolf_vocab, VOCAB_FSIZE);
    load_file("wolf.chr", wolf_font, CHR_FSIZE);
    if (Sum(Goober, 0x24) != sum_goober + (int) wolf_font) {_exit(-1);}
    RdSysFnt(wolf_font);
    file_to_screen(1);
    if (wait_to_return()) /* play demo if the return key isn't pressed in time*/
        {load_demo();}
    while (true)
    {   b284 = false;
        l1a = 0x8000;
        l18 = 0x8002;
        lroom_pg = (byte *) &rm_pg;
        lcastle_pg = &cstl_pg;
        is_cstle_stt_60(); /*controller = undefined*/;
        if (!isDemo)
        {   while (controller == DEV_undefined)
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
            if (controller == DEV_joystick && !lkfr_jystk())
                {lack_jystk();}
            }
            if (controller == DEV_joystick && joyCunfag == 0x59)
                {jystk_cnfg();}
            if (cstl_load_var == 0)
                {resume_castle();}
            else if (cstl_load_var < 0x80)
            {   setVideoMode(PxlClrLo);
                PositCPuts(13, 6, "Loading castle, please wait...");
                reload_castle();
            }
            else
            {   setVideoMode(PxlClrLo);
                PositCPuts(13, 4, "Creating new castle, please wait...");
                new_castle();
            }
        }
        for (i=0; i<0x48; ++i)
        {   (&cstl_pg.s_80)[i] = 0;}
        fun728c();
        setVideoMode(PxlClrLo);
        pdmodt = (byte *) &dmodt_buffer;
        prng0 = 0xacb6;
        prng1 = 0x38fa;
        GfxFileP = dmodt_buffer.gfx_buffer;
        game();
        if (isDemo || error_encountered) {break;}
        if (!cstl_pg.save_status) {
            setVideoMode(PxlClrLo);
            PositCPuts(13,11,"Saving the game");
        }
        save_room_pg();
        save_castle("castle");
    }
    b4ac0 = false;
    isDemo = false;
    dminpind = 0;
    dmodt_offset = 0;
    goto outer_loop;
}

void
is_cstle_stt_60(void)
{   
    cstl_load_var = (cstl_pg.save_status == 0x60) ?
                  0xff : 
                  cstl_pg.save_status;
    controller = DEV_undefined; 
    rank_index = rank_calculate();
}


void start_menu(void)
{
    char c;
    rank_print();
    PositCPuts(7, 1, "Press:");
    PositCPuts(9, 6, "Ctrl-N To create a new");
    PositCPuts(10, 13, "castle map only.");
    PositCPuts(11, 13, "(Saving your rank)");
    PositCPuts(13, 6, "Ctrl-R To create a new");
    PositCPuts(14, 13, "castle map and");
    PositCPuts(15, 13, "reset your rank to");
    PositCPuts(16, 13, "Private.");
    PositCPuts(18, 6, "ENTER to do nothing.");
    while (true)
    {
        while (!IsKStrok());
        c = GetStrok();
        if (c == CTRL('R'))
        {   rank_index = RNK_PRIVATE;
            cstl_load_var = 0xff;
        }
        else if (c == CTRL('N'))
        {   cstl_load_var = 0xff;

        }
        else if (c != '\r')
        {
            continue;
        }
        break;
    }
}

void reverse_control(void)
{
    char c;
    setVideoMode(PxlClrLo);
    PositCPuts(9, 2, "What controls do you wish to adjust ?");
    PositCPuts(11, 2 , "Press: K to adjust keyboard controls");
    PositCPuts(13, 9, "J to adjust joystick controls");
    while (true)
    {   while (!IsKStrok());
        c = GetStrok();
        if ((c | 0x20) == 'k')
        {   kb_cnfg();}
        else if ((c | 0x20) == 'j')
        {   if (lkfr_jystk() == 0)
                {jystk_cnfg();}
            else
                {lack_jystk();}
        }
        else
            {continue;}
        break;
    }
}




void resume_castle(void)
{
    setVideoMode(PxlClrLo);
    PositCPuts(13, 6, "Resuming where you left off...");
    ld_castle_page_w_ptr("castle", CASTLE_FSIZE);
    rank_write(rank_index);
    load_room_pg(cstl_pg.rm_id);
    if (!cstl_pg.act_timer) {b2aa = true;}
    cstl_pg.save_status = 1;
    save_castle("castle");
    if (!build_func_on_stack(35)) 
        {cstl_pg.save_status = 0;}
    else
    {   cstl_pg.save_status = 0x40;
        error_encountered = (cstl_pg.bulletCount + cstl_pg.rm_id) | 0xAA;
    }
}

void new_castle(void)
{
    int index;
    ld_castle_page_w_ptr("sektor", CASTLE_FSIZE);
    sektor_indexize();
    scramble_castle();
    f44db();
    f45e9();
    rank_write(rank_index);
    scramble_castle();
    f46c2();
    load_room_pg(1);
    cstl_reset();
    cstl_pg.save_status = 1;
    save_castle("castle");
    cstl_pg.save_status = 0;
    save_castle("backup");
    cstl_pg.room_timer = 0;
    if (build_func_on_stack(35))
    {   cstl_pg.save_status = 0x40;
        error_encountered = cstl_pg.tile_pl_rm + 0x40;
    }
}

void reload_castle(void)
{
    if (cstl_pg.rank_index < RNK_CORPORAL)
        {ld_castle_page_w_ptr("castle", CASTLE_FSIZE);}
    else 
        {ld_castle_page_w_ptr("backup", CASTLE_FSIZE);}
    rank_write(rank_index);
    load_room_pg(1);
    cstl_reset();
    cstl_pg.save_status = 1;
    save_castle("castle");
    cstl_pg.room_timer = 0;
    cstl_pg.save_status = 0;
    if (build_func_on_stack(35))
    {   cstl_pg.save_status = 0x40;
        error_encountered = 0x40;
    }
}



void ld_castle_page_w_ptr(filename, length)
string filename;
{
    int i;
    byte *cstl;
    cstl = (byte *) &cstl_pg;
    load_file(filename, file_buffer, length);
    for (i=0; i < PAGE_SZ; ++i)
    {   cstl[i] = pg0_file_buffer[i];
    }
    
}


void save_castle(file_name)
string file_name;
{
    int fildsc, i;
    byte *cstl;
    cstl = (byte *) &cstl_pg;
    pg0_file_buffer = file_buffer;
    for (i=0; i < PAGE_SZ; ++i) 
        {pg0_file_buffer[i] = cstl[i];}
    fildsc = checked_open(file_name, O_RAW | O_WRONLY);
    if (write(fildsc, file_buffer, CASTLE_FSIZE) < 0)
    {    put_2_strings("Error writing file ", file_name);
        _exit(-1);
    }
    close(fildsc);
}

string rank_table[8] = {
    "Private",
    "Corporal",
    "Sergeant",
    "Lieutenant",
    "Captain",
    "Colonel",
    "General",
    "Field Marshal"
};

void rank_print(void)
{
    setVideoMode(PxlClrLo);
    PositCPuts(2, 1, "Your Rank is ");
    cputs(rank_table[rank_index >> 5]);
    /*cprintf("\n rank index: 0x%x\n shifted: %x\n rank: %s\n first rank: %s",
           rank_index, rank_index >> 5, rank_table[rank_index >> 5], *rank_table);*/
}

signed_error load_room_pg(pagenumb)
int pagenumb;
{
    int i;
    page *rmp = (page *) &rm_pg;
    if ((0 < pagenumb) && (pagenumb < 0x3d))
    {   pagenumb <<= 8;
        for (i=0; i < PAGE_SZ; ++i)
            {*rmp[i] = file_buffer[pagenumb++];}
        return 0;
    }
    else {return -1;}
}

void save_room_pg(void)
{   byte rmid;
    page* pfilbuf;
    byte* rmpg;
    int i;
    word pg;
    rmid = cstl_pg.rm_id;
    pfilbuf = (page *) &file_buffer;
    pg = rmid;
    rmpg = (byte *) &rm_pg;
    for (i=0; i < PAGE_SZ; ++i)
    {
        pfilbuf[pg][i] = rmpg[i];
    }

    
}

byte rank_calculate(void)
{
    bool cont;
    cprintf(" save status:%x\n rank_index: %x\n rise rank twice: %x\n"
    ,cstl_pg.save_status, cstl_pg.rank_index, cstl_pg.plans);
    if (cstl_pg.save_status < 0x80)
    {   if (1 < cstl_pg.save_status)
            {--cstl_pg.rank_index;}
    }
    else
    {   do
        {   if (RNK_FIELD_MARSHAL <= cstl_pg.rank_index) {break;}
            cstl_pg.rank_index += 0x10;
            cont = cstl_pg.plans;
            cstl_pg.plans = false;
        } while (cont);
        if (RNK_FIELD_MARSHAL < cstl_pg.rank_index) 
            {cstl_pg.rank_index = RNK_FIELD_MARSHAL;}
    }
    if (cstl_pg.rank_index < RNK_PRIVATE)
        {cstl_pg.rank_index = RNK_PRIVATE;}
    cprintf("rank index: %x\n", cstl_pg.rank_index);
    return cstl_pg.rank_index;
}

void rank_write(rnk_ind)
{
    cstl_pg.rank_index = (byte) rnk_ind;
    if (cstl_load_var)
        {cstl_pg.plans = false;}
}

int
sektor_indexize(void)
{
    int i;

    for (i=1; i < 0x40; ++i)
      {file_buffer[i * PAGE_SZ + 0x50] = (byte) i;}
    return i;
}

bool pcjr;

void put_2_strings(line4, line5)
string line4, line5;
{   
    if (pcjr) {setVideoMode(TxtGreyWd);}
    else {setVideoMode(TxtGreyThn);}
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(4,1));
    cputs(line4);
    cputs(line5);
}

struct {
    byte f0[500];
    byte f1[500];
    byte gfx_buffer[GFX_BSIZE];
}   dmodt_buffer;
extern bool horizontal;

void load_demo(void)
{
    byte *dmgfx_buffer;
    file_to_screen(2);
    ld_castle_page_w_ptr("demofile", CASTLE_FSIZE);
    load_file("demodata", &dmodt_buffer, DEMODT_FSIZE);
    isDemo = true;
    horizontal = false;
    dmgfx_buffer = dmodt_buffer.gfx_buffer;
    dmodt_offset = 0;
    dminpind = 0;
    GfxFileP = dmgfx_buffer;
    load_room_pg(1);
}

bool wait_to_return(void)
{
    long limit, li;
    if (error_encountered) {return 1;}
    if (!pcjr) {limit = 119000l;}
    else {limit = 56000l;}
    for (li=0;li <= limit;++li)
    {   if (IsKStrok())
        {   if (GetStrok() == '\r')
                {return false;}
        }
    }
    return true;
}

int load_file(file_name, dest, length)
string file_name;
byte *dest;
int length;
{
    int fildsc, status;
    isDos210();
    if (Goober(0x23, dest) > 0) {_exit(-1);} 
    fildsc = status = checked_open(file_name, O_RAW);
    if (-1 < read(fildsc, dest, length))
    {   status = close(fildsc);    
    }
    else
    {   put_2_strings("Error reading ", file_name);
        if (fildsc > -1) {close(fildsc);}
        _exit(-1);
    }
    return status;
}


void lack_jystk(void)
{   /*lack_of joystick*/
    wait_for_input(0,0x17, "\aNo joystick connected (Press space bar)", ' ');
    controller = DEV_undefined;
}

