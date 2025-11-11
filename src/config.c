#include "cw.h"
#include "video.h"
#include "FCNTL.H"
#include "config.h"

#ifdef __WATCOMC__ 
#include "conio.h"
#include "cwa.h"
#include "anti_debug.h"
#include "io1.h"
#include "game_files.h"
#include "CtrlConfig.h"

int w_ctrls_load(void);
void print_to_position(byte column, byte row, string massage);
#endif

extern byte RGB_monitor;
extern bool horizontal;


void kb_cnfg(void) 
{ /*keyboard config*/
  char *move, *shoot;
  char stroke;
  setVideoMode(PxlClrLo);
  if (!horizontal)
  { move = "left";
    shoot = "right";
  }
  else
  { move = "right";
    shoot = "left";
  }
  PositCPrintf(5, 1, "You now move with your %s hand",move);
  PositCPrintf(7, 1, "and shoot with your %s hand.",shoot);
  print_to_position(8, 9, "Press the ESC key");
  PositCPrintf(12, 1, "to move with your %s hand, and", shoot);
  PositCPrintf(14, 1, "shoot with your %s hand.", move);
  print_to_position(0, 16, "Press the space bar to keep");
  print_to_position(0, 18, "the controls as they currently are.");
  stroke = '\0';
  while (stroke != ESC && (stroke != ' ')) {
    if (IsKstroke() != 0) {
      stroke = (char)Getstroke();
    }
  }
  if (stroke == ESC) {
    horizontal = !horizontal;
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl((23), (14)));
    print_to_position(13, 22, "Saving data...");
    w_ctrls_load();
  }
}

void select_monitor(void) 
{
  byte oldRGB;
  char key;
  oldRGB = RGB_monitor;
  if (RGB_monitor == 'Y') {
    RGB_monitor = 0;
  }
  setVideoMode(PxlClrLo);
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
  while ((key != ESC && (key != ' '))) {
    if (IsKstroke() != 0) {
      key = Getstroke();
    }
  }
  RGB_monitor = key == ESC;
  if (RGB_monitor != oldRGB) {
    print_to_position(14, 22,"Saving data...");
    w_ctrls_load();
    print_to_position(14, 22,"\t\t ");
  }
}

void print_to_position(column, row, massage) 
byte column, row; 
string massage;
{
    PositCPuts(row+1, column+1, massage);
}

bool horizontal, sagital;
byte LC_L_RC[0xb], RC_DC[0xb], UC_DC_U[0xb], DC_UC[0xb];
extern byte joyCunfag;


void r_ctrls_load(void)
{
    int fd;
    if (check_for_debugger()) {_exit(-1);}
    fd = open("ctrls", O_RAW); /* doesn't use drive letter*/
    if (fd < 0) 
    {
        put_2_strings("Cannot open control file", "");
        _exit(-1);
    }
    ctrls_read(fd, &horizontal, 0l, 1);
    ctrls_read(fd, &sagital, 1l, 1);
    ctrls_read(fd, &joyCunfag, 2l, 1);
    ctrls_read(fd, &RGB_monitor, 3l, 1);
    ctrls_read(fd, LC_L_RC, 4l, 0xb);
    ctrls_read(fd, RC_DC, 0xfl, 0xb);
    ctrls_read(fd, UC_DC_U, 0x1al, 0xb);
    ctrls_read(fd, DC_UC, 0x25l, 0xb);
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
        cprintf("%x",offset);
        _exit(-1);
    }
    return length;
}

int w_ctrls_load(void)
{
  int fd;
  fd = open("ctrls",O_RAW | O_WRONLY);
  if (fd < 0)
  { cputs("Cannot open control file");
    exit(-1);
  }
    ctrls_write(fd, &horizontal, 0l, 1);
    ctrls_write(fd, &sagital, 1l, 1);
    ctrls_write(fd, &joyCunfag, 2l, 1);
    ctrls_write(fd, &RGB_monitor, 3l, 1);
    ctrls_write(fd, LC_L_RC, 4l, 0xb);
    ctrls_write(fd, RC_DC, 0xfl, 0xb);
    ctrls_write(fd, UC_DC_U, 0x1al, 0xb);
    ctrls_write(fd, DC_UC, 0x25l, 0xb);
    return close(fd);
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
