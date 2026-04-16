#include "cw.h"
#include "video.h"
#include "files.h"
#include "FCNTL.H"
#include "config.h"
#include "IVT.h"
#include "memory.h"
#include "init.h"

extern bool isDemo;
extern word dmodt_offset, dminpind, error_encountered;
extern byte controller;

#ifdef __WATCOMC__
#include "conio.h"
#include "memory.h"
#include "cwa.h"
#include "io1.h"
#include "peripherals.h"
#endif

int
sektor_indexize(void)
{
    int i;

    for (i=1; i < 0x40; ++i)
      {file_buffer[i * PAGE_SZ + 0x50] = (byte) i;}
    return i;
}

word a77a2[11] =
{   0, 4,  8, 0,
    2, 6, 10, 0,
    1, 5,  9,

};


int f11ec(void)
{   byte tl_pos;
    uint front;
    if (!cstl_pg.aim_dir) {return -1;}
    tl_pos = cstl_pg.tile_pl_rm;
    if 
    (cstl_pg.aim_dir != DIR_UP)
        {tl_pos += 8;}
    if (rm_pg.tl_tble[tl_pos / 8][tl_pos % 8] & a77a2[cstl_pg.aim_dir] != 0) {return -1;}
    front = in_front(cstl_pg.tile_pl_rm, cstl_pg.aim_dir);
    if ((-1 < col_row2b2.col) && (col_row2b2.col < 8) &&
        (-1 < col_row2b2.row) && (col_row2b2.row < 9) &&
        (rm_pg.tl_tble[front / 8][front % 8] & a77a2[cstl_pg.aim_dir] == 0)) {return front;}
    else {return -1;}
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
    {   if (IsKstroke())
        {   if (Getstroke() == '\r')
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

void fgame_1585(void)
{
    cputs("unimplemented");
}

byte table_789e[24][40];

void wolf_draw(str, color, row, ln_start, col)
char * str;
{
    for (;*str != '\0';++str)
    {
        if (*str == '\r')
        {   ++row;
            if (row > 24) {row = 0;}
            col = ln_start;
        }
        else
        {   /* write charecter once in row and col
               in blue if the charecter is an SS insignia
               in argument color otherwise
            */
            BiosVideo(SET_CURSOR_POSITION, 0, 0, 0x100*row + col);
            if (*str == 0xb9)
            {   BiosVideo(0xb9 | WRITE_CHAR_COLOR, BlueFG, 1, 0);}
            else
            {   BiosVideo(*str | WRITE_CHAR_COLOR, (byte) color, 1, 0);}
            table_789e[row][col] = *str;
            ++col;
        }
    }
}

