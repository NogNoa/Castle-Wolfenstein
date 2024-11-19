#include "cw.h"
#include "FCNTL.H"
#include "ibm.h"

byte prewrite_buffer[0x100];
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


