#include "cw.h"
#include "files.h"
#include "video.h"

byte prewrite_buffer[PAGE_SZ];
char file_buffer[0x3ff4];
char* ptr_file_buffer = file_buffer;

int checked_open(fn, flags)
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

resume_castle(/*void*/)
{
    setVideoMode(PxlClrLo);
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(13,6));
    cputs("Resuming where you left off...");
    
}

char pg_a[PAGE_SZ];
struct 
{
    byte prefix[0x60];
    byte save_status;
    byte suffix[PAGE_SZ-0x61]
} castl_pg;

ld_castle_page_w_ptr(filename, length)
string filename;
{   
    int i;
    byte cstl[PAGE_SZ] = &castl_pg;
    load_file(filename, file_buffer, length);
    for (i=0; i < PAGE_SZ; ++i)
    {   cstl[i] = ptr_file_buffer[i];
    }
}

write_to_file(file_name)
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

word dmodt_offset, ind29a;
bool isDemo = false;
byte* gfx_fp;
byte dmodt_buffer[DEMODT_FSIZE];
extern bool horizontal;

load_demo()
{
    byte* gfx_buffer;
    file_to_screen(2);
    ld_castle_page_w_ptr("demofile", CASTLE_FSIZE);
    load_file("demodata", dmodt_buffer, DEMODT_FSIZE);
    isDemo = true;
    horizontal = false;
    gfx_buffer = dmodt_buffer +  1000;
    dmodt_offset = 0;
    ind29a = 0;
    gfx_fp = gfx_buffer;
    load_page_a(1);
}

word error_encountered;
extern bool pcjr;

bool wait_to_return()
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

load_file(file_name,dest, length)
string file_name;
byte *dest;
int length;
{
    int fildsc;
    isDos210();
    if (Goober(0x23, dest) > 0) {_exit(-1);}
    fildsc = checked_open(file_name, 0x8000);
    if (read(fildsc, dest, length) < 0)
    {   put_2_strings("Error reading ", file_name);
        if (fildsc > -1) {close(fildsc);}
        _exit(-1);
    }
    close(fildsc);
}


