#include "cw.h"
#include "files.h"
#include "video.h"
#include "game_f~1.h"
#include "config.h"
#include "IVT.h"
#include "memory.h"

#ifdef __WATCOMC__
#include "console.h"
#include "FCNTL.H"
#include "ibm.h"
#include "io1.h"
#include "cwa.h"
#include "peripherals.h"
#include "config.h"
int Goober(int p1, byte* dest);
void rank_print(void);
#endif

byte prewrite_buffer[0x100];
char file_buffer[0x3ff4];
char* ptr_file_buffer = file_buffer;
byte rank_index;

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
            cstl_pg.save_status = 0xff;
        }
        else if (c == CTRL('N'))
        {   cstl_pg.save_status = 0xff;

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
}


struct cs_pg_t cstl_pg;

void ld_castle_page_w_ptr(filename, length)
string filename;
{
    int i;
    byte *cstl;
    cstl = (byte *) &cstl_pg;
    load_file(filename, file_buffer, length);
    cprintf("ld_castle: ptr_file_buffer = file_buffer[$%x]\n", ptr_file_buffer - file_buffer);
    for (i=0; i < PAGE_SZ; ++i)
    {   cstl[i] = ptr_file_buffer[i];
    }
    
}


void write_to_file(file_name)
string file_name;
{
    int fildsc, i;
    ptr_file_buffer = file_buffer;
    for (i=0; i < PAGE_SZ; ++i) 
        {ptr_file_buffer[i] = prewrite_buffer[i];}
    fildsc = checked_open(file_name, 0x8001);
    if (write(fildsc, file_buffer, 0x3ff4) < 0)
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
    cprintf("\n rank index: 0x%x\n shifted: %x\n rank: %s\n first rank: %s",
           rank_index, rank_index >> 5, rank_table[rank_index >> 5], *rank_table);
}

signed_error load_page_a(pagenumb)
int pagenumb;
{
    int i;
    if ((0 < pagenumb) && (pagenumb < 0x3d))
    {   pagenumb <<= 8;
        for (i=0; i < PAGE_SZ; ++i)
            {pg_a[i] = file_buffer[pagenumb++];}
        return 0;
    }
    else {return -1;}
}

byte rank_calculate(void)
{
    bool cont;
    cprintf(" save status:%x\n rank_index: %x\n rise rank twice: %x\n"
    ,cstl_pg.save_status, cstl_pg.rank_index, cstl_pg.ris_rnk_twc);
    if (cstl_pg.save_status < 0x80)
    {   if (1 < cstl_pg.save_status)
            {--cstl_pg.rank_index;}
    }
    else
    {   do
        {   if (RNK_FIELD_MARSHAL <= cstl_pg.rank_index) {break;}
            cstl_pg.rank_index += 0x10;
            cont = cstl_pg.ris_rnk_twc;
            cstl_pg.ris_rnk_twc = false;
        } while (cont);
        if (RNK_FIELD_MARSHAL < cstl_pg.rank_index) 
            {cstl_pg.rank_index = RNK_FIELD_MARSHAL;}
    }
    if (cstl_pg.rank_index < RNK_PRIVATE)
        {cstl_pg.rank_index = RNK_PRIVATE;}
    cprintf("rank index: %x\n", cstl_pg.rank_index);
    return cstl_pg.rank_index;
}

void
castle_indexize(void)
{
    int i;

    for (i=1; i < 0x40; ++i)
      {file_buffer[i * PAGE_SZ + 0x50] = (byte) i;}
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

word dmodt_offset, ind29a;
bool isDemo = false;
byte dmodt_buffer[DEMODT_FSIZE];
extern bool horizontal;

void load_demo(void)
{
    byte *gfx_buffer;
    file_to_screen(2);
    ld_castle_page_w_ptr("demofile", CASTLE_FSIZE);
    load_file("demodata", dmodt_buffer, DEMODT_FSIZE);
    isDemo = true;
    horizontal = false;
    gfx_buffer = dmodt_buffer + 1000;
    dmodt_offset = 0;
    ind29a = 0;
    GfxFileP = gfx_buffer;
    load_page_a(1);
}

word error_encountered;

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
    fildsc = status = checked_open(file_name, 0x8000);
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

int d2ae, d29c;

void isPcJr(void)
{
  SegMemSet(SingleStep+1, 0x34);
  SegMemSet(SingleStep+3, 0xff);
  if (SegmGt(0xf000, (byte *)0xffff) == 0xfd) /* from the PC Jr BIOS*/
  { pcjr = true;
    d2ae = 900;
    d29c = 200;
  }
  else
  { pcjr = false;
    d2ae = 3300;
    d29c = 600;
  }
  SegMemSet(Breakpoint+1, 0xcd);
  SegMemSet(Breakpoint+3, 0x13);
}
