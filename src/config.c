#include "cw.h"
#include "video.h"
#include "IVT.h"
#include "FCNTL.H"

static int d2ae, d29c;
bool pcjr;

put_2_strings(line0, line1)
char *line0, *line1;
{   
    if (pcjr) {setVideoMode(TXT_GREY_WD);}
    else {setVideoMode(TXT_GREY_THN);}
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(4,1));
    cputs(line0);
    cputs(line1);
}


isPcJr()
{
  SegMemSet(SingleStep+1, 0x34);
  SegMemSet(SingleStep+3, 0xff);
  pcjr = (SegmGt(0xf000, (char *)0xffff) == 0xfd); /* from the PC Jr BIOS*/
  if (pcjr)
  { d2ae = 3300;
    d29c = 600;
  }
  else
  { d2ae = 900;
    d29c = 200;
  }
  SegMemSet(IntBreakpoint+1, 0xcd);
  SegMemSet(IntBreakpoint+3, 0x13);
}

extern byte RGB_monitor;


keyboard_config(void) {}

select_monitor() 
{
  byte oldRGB;
  char key;
  oldRGB = RGB_monitor;
  if (RGB_monitor == 'Y') {
    RGB_monitor = 0;
  }
  setVideoMode(4);
  print_to_position(0,1,"The two ways in which your monitor may");
  print_to_position(0,2,"be connected to your computer are either");
  print_to_position(0,3,"as an RGB or a Non-RGB monitor.");
  print_to_position(0,5,"Currently, your monitor is assumed to be");
  print_to_position(0,6,"connected as a");
  if (RGB_monitor == 0) {
    cputs(" Non-");
  }
  else {
    cputs("n ");
  }
  cputs("RGB monitor.");
  print_to_position(0, 8,"If set incorrectly, the hi-resolution");
  print_to_position(0, 9,"graphic screens may appear distorted");
  print_to_position(0, 10,"and/or improperly colored.");
  print_to_position(0, 12,"Press the ESC key if you are using");
  print_to_position(0, 13,"an RGB monitor hookup.");
  print_to_position(0, 15,"Press the space bar if you are using");
  print_to_position(0, 16,"a Non-RGB monitor hookup.");
  key = '\0';
  while ((key != '\e' && (key != ' '))) {
    if (IsKeystroke() != 0) {
      key = GetStroke();
    }
  }
  RGB_monitor = key == '\e';
  if (RGB_monitor != oldRGB) {
    print_to_position(14, 22,"Saving data...");
    ctrls_load_w();
    print_to_position(14, 22,"\t\t ");
  }
  return;
}

print_to_position(column, row, massage) 
byte column, row;
string massage;
{
    BiosVideo(SET_CURSOR_POSITION, 0, 0, (int)row << 8 | column);
    cputs(massage);
}

bool horizontal, vertical;
byte b2ba, RGB_monitor, b4ac3[0xb], b4ace[0xb], b4ad9[0xb], b4ae4[0xb];

ctrls_load_r()
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

int ctrls_read(fd, buf, offset, nbytes)
int fd; byte *buf; long offset; int nbytes;
{
    int length;
    lseek(fd, offset, 0);
    length = read(fd, buf, nbytes);
    if (length != nbytes)
    {   put_2_strings("Error reading control file!", "");
        _exit(-1);
    }
    return length;
}

int ctrls_write(ctrls, buffer, offset, length)
int ctrls, length;
string buffer;
long offset;
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
