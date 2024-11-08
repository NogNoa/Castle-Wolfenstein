#include "cw.h"
#include "FCNTL.H"
#include "STDLIB.H"
#include "memory.h"
#include "console.h"
#include "anti_debug.h"

bool b4b39, b4b3a, affirmation;
byte b2ba, b4ac3[0xb], b4ace[0xb], b4ad9[0xb], b4ae4[0xb];

int ctrls_read(fd, buf, offset, nbytes)
int fd; byte *buf; long offset; int nbytes;
{
    int length;
    lseek(fd, offset, 0);
    length = read(fd, buf, nbytes);
    if (length != nbytes)
    {   put_2_lines("Error reading control file!", "");
        _exit(-1);
    }
    return length;
}

void ctrls_load()
{
    int fd;
    if (check_for_debugger()) {_exit(-1);}
    fd = open("ctrls", O_RAW); /* doesn't use drive letter*/
    if (fd < 0) 
    {
        put_2_lines("Cannot open control file", "");
        _exit(-1);
    }
    ctrls_read(fd, &b4b39, 0, 1);
    ctrls_read(fd, &b4b3a, 1, 1);
    ctrls_read(fd, &b2ba, 2, 1);
    ctrls_read(fd, &affirmation, 3, 1);
    ctrls_read(fd, b4ac3, 4, 0xb);
    ctrls_read(fd, b4ace, 0xf, 0xb);
    ctrls_read(fd, b4ad9, 0x1a, 0xb);
    ctrls_read(fd, b4ae4, 0x25, 0xb);
    close(fd);
}
