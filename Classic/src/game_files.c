#include "cw.h"
#include "console.h"
#include "STDLIB.H"
#include "FCNTL.H"
#include "ibm.h"

byte prewrite_buffer[0x100];
char file_buffer[0x3ff4];
char* ptr_file_buffer = file_buffer;

inline int checked_open(string fn, int flags)
{   int fildsc;
    fildsc = open(fn, flags);
    if (fildsc < 0) 
    {   put_2_strings("Cannot open ", fn);
        _exit(-1);
    }
    return fildsc;
}

void write_to_file(string file_name)
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

int goober_function(int p1, void* dest);

void load_file(string file_name, void *dest, int length)
{
    int fildsc;
    isDos210();
    if (goober_function(0x23, dest) > 0) {_exit(-1);}
    fildsc = checked_open(file_name, 0x8000);
    if (read(fildsc, dest, length) < 0)
    {   put_2_strings("Error reading ", file_name);
        if (fildsc > -1) {close(fildsc);}
        _exit(-1);
    }
    close(fildsc);
}


