
#include "cw.h"
#include "video.h"
#include "init.h"

extern bool pcjr;
extern bool b2aa;

#ifdef __WATCOMC__
#include "conio.h"
#include "sonara.h"
#include "cwa.h"
#include "init2.h"
byte qpull(void);
byte olqpull(void);
#endif

int qstart, qstop;
byte queue[0x20];

void 
clear_queue()
{
    while (qpull());
}


byte
qpull()
{
    return olqpull();
}

byte
olqpull()
{
    byte back;
    
    if (qstart == qstop) {
        return 0;
    }
    back = queue[qstart];
    queue[qstart++] = 0;
    qstart %= 0x20;
    return back;
}

void
qpush(call)
byte call;
{
  queue[qstop++] = call;
  qstop %= 0x20;
}

void
qpara_push(call)
uint call;
{
  call &= 0xf;
  if (call > 4){ call >>= 2;}
  qpush((byte)call);
}

game()
{   puts("not nearly implemented");
}


void escf1_prmpt(void)
{
  char c = '\0';
  if (cstl_pg.s_87 == cstl_pg.rm_id)
    {StpSon();}
  if (!pcjr)
    {setVideoMode(TxtGreyThn);}
  else
    {setVideoMode(TxtGreyWd);}
  PositCPuts(2,1,"A>");
  while (c != KEY_F1 && c != ESC)
  {   c = (char) wait_kb();
      if (!c)
      { c = (char) GetStroke();
        if (c < 0x80) {c += 0x80;}
        else {c = '\0';}
      }
  }
  if (c == KEY_F1)
  { fgame_1585();
    if (cstl_pg.s_87 == cstl_pg.rm_id) {Speak99();}
    if (cstl_pg.act_timer) {b2aa = true;}
  }
  else
  {
    BiosVideo(SET_CURSOR_POSITION, 0, 0, 0);
    _exit(-1);
  }
}