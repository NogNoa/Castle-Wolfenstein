#include "cw.h"
#include "FCNTL.H"

bool b4b39, b4b3a, affirmation;
byte b2ba, b4ac3[0xb], b4ace[0xb], b4ad9[0xb], b4ae4[0xb];

void ctrls_load()
{
    if (f0313()) {_exit(-1);}
    int fd = open("ctrls", O_RAW);
    if (fd < 0) 
    {
        put_2_lines("Cannot open control file", "");
        _exit(-1);
    }
    load(fd, &b4b39, 0, 1);
    load(fd, &b4b3a, 1, 1);
    load(fd, &b2ba, 2, 1);
    load(fd, &affirmation, 3, 1);
    load(fd, b4ac3, 4, 0xb);
    load(fd, b4ace, 0xf, 0xb);
    load(fd, b4ad9, 0x1a, 0xb);
    load(fd, b4ae4, 0x25, 0xb);
    close(fd);
}

int load(fd, buf, offset, nbytes)
int fd; byte *buf; long offset; int nbytes;
{
    lseek(fd, offset, 0);
    int length = read(fd, buf, nbytes);
    if (length != nbytes)
    {   put_2_lines("Error reading control file!", "");
        _exit(-1);
    }
    return length;
}
