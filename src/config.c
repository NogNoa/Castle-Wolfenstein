#include "cw.h"
#include "video.h"
#include "conio.h"
#include "CtrlConfig.h"

extern byte RGB_monitor;

void print_to_position(byte column, byte row, string massage);

void keyboard_config(void) {}
void select_monitor(void) 
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
    if (Is_Keystroke() != 0) {
      key = get_stroke();
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

void print_to_position(byte column, byte row, string massage) 
{
    BiosVideo(SET_CURSOR_POSITION, 0, 0, (int)row << 8 | column);
    cputs(massage);
}
