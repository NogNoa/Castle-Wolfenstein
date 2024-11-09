#include "cw.h"
#include "console.h"
#include "STDLIB.H"
#include "FCNTL.H"

byte prewrite_buffer[0x100];
char file_buffer[0x3ff4];
char* ptr_file_buffer = file_buffer;

void write_to_file(string file_name)
{
    int fildsc, i;
    ptr_file_buffer = file_buffer;
    for (i=0; i < 0x100; ++i) 
        {ptr_file_buffer[i] = prewrite_buffer[i];}
    fildsc = open(file_name, 0x8001);
    if (fildsc < 0) 
    {   put_2_strings("Cannot open ", file_name);
        _exit(-1);
    }
    if (write(fildsc, file_buffer, 0x3ff4) < 0)
    {    put_2_strings("Error writing file ", file_name);
        _exit(-1);
    }
    close(fildsc);
}
