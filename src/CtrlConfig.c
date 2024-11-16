#include "cw.h"
#include "FCNTL.H"
#include "STDLIB.H"
#include "memory.h"
#include "console.h"
#include "anti_debug.h"

bool horizontal, vertical;
byte b2ba, RGB_monitor, b4ac3[0xb], b4ace[0xb], b4ad9[0xb], b4ae4[0xb];

int ctrls_read(int ctrls, string buffer, long offset, int length)
{
    int nbytes;
    lseek(ctrls, offset, 0); /*start+ offset*/
    nbytes = read(ctrls, buffer, length);
    if (nbytes != length)
    {   put_2_strings("Error reading control file!", "");
        _exit(-1);
    }
    return nbytes;
}

int ctrls_write(int ctrls, string buffer, long offset, int length)
{
    int nbytes;
    lseek(ctrls, offset, 0); /*start+ offset*/
    nbytes = write(ctrls, buffer, length);
    if (write(ctrls, buffer, length) != length)
    {   cputs("Error writing control file!");
        _exit(-1);
    }
    return nbytes;
}


void ctrls_load_r()
{
    int fd;
    if (check_for_debugger()) {_exit(-1);}
    fd = open("ctrls", O_RAW); /* doesn't use drive letter*/
    if (fd < 0) 
    {
        put_2_strings("Cannot open control file", "");
        _exit(-1);
    }
    ctrls_read(fd, &horizontal, 0, 1);
    ctrls_read(fd, &vertical, 1, 1);
    ctrls_read(fd, &b2ba, 2, 1);
    ctrls_read(fd, &RGB_monitor, 3, 1);
    ctrls_read(fd, b4ac3, 4, 0xb);
    ctrls_read(fd, b4ace, 0xf, 0xb);
    ctrls_read(fd, b4ad9, 0x1a, 0xb);
    ctrls_read(fd, b4ae4, 0x25, 0xb);
    close(fd);
}
