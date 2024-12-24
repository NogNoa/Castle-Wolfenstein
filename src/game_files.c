#include "cw.h"
#include "files.h"


byte prewrite_buffer[0x100];
char file_buffer[0x3ff4];
char* ptr_file_buffer = file_buffer;

#define PG_SZ 0x100

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

char pg_a[PG_SZ];
char pg_b[PG_SZ];

p_ld_pg_b(filename, length)
string filename;
{   
    int i;
    load_file(filename, file_buffer, length);
    for (i=0; i < PG_SZ; ++i)
    {   pg_b[i] = ptr_file_buffer[i];
    }
}

write_to_file(file_name)
string file_name;
{
    int fildsc, i;
    ptr_file_buffer = file_buffer;
    for (i=0; i < 0x100; ++i) 
        {ptr_file_buffer[i] = prewrite_buffer[i];}
    fildsc = checked_open(file_name, 0x8001);
    if (write(fildsc, file_buffer, 0x3ff4) < 0)
    {    put_2_strings("Error writing file ", file_name);
        _exit(-1);
    }
    close(fildsc);
}


word dmodt_offset, w29a;
bool b7716 = false;
word gfx_fp;
byte dmodt_buffer[DEMODT_FSIZE];
extern bool horizontal;

load_demo()
{
    word l4;
    file_to_screen(2);
    load_castle_page_w_ptr("demofile", CASTLE_FSIZE);
    load_file("demofata", dmodt_buffer, DEMODT_FSIZE);
    b7716 = true;
    horizontal = false;
    l4 = 0x7c62;
    dmodt_offset = 0;
    w29a = 0;
    gfx_fp = l4 + 0x3e8;
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


