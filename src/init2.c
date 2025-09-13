#include "cw.h"
#include "video.h"
#include "files.h"
#include "FCNTL.H"
#include "config.h"

extern bool isDemo;
extern word dmodt_offset, dminpind, error_encountered;
extern char controller;

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