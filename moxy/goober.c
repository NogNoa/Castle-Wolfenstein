#include "cw.h"
#include "anti_debug.h"
#include "IVT.h"
int OnStack();

bool build_func_on_stack(int arg)
{
  register int *bp;
  int fnstk[8];
  fnstk[0] = 0x1b8;
  fnstk[1] = 0xbb02;
  fnstk[2] = 0x7c62;
  fnstk[3] = 0x1b8;
  fnstk[4] = arg + 0xba00;
  fnstk[5] = *default_drive;
  fnstk[6] = 0x9090;
  fnstk[7] = 0xcb;
  OnStack();
  fnstk[0] = 0x1000;
  for (arg=1; arg < 8; ++arg)
  {     fnstk[arg] = 0;

  }
  return (fnstk[0] == 0x1000);
}

static int i5ff9 = 0x1000;
static word* p5ff0 = 0;
static int si;

void
del_inst_5ff9(void)
{
    i5ff9 = 0x9090;
}

int goober_function(int p1, void* dest)
{
    int a;
    byte i;
    (void)p1;
    p5ff0 = dest;
    switch(i5ff9)
    {case 0x1000:
        *(si + p5ff0) += *default_drive;
        break;
    case 0x9090:
        break;
    case 0x200:
        *(si + p5ff0) = 1;
        break;
    }
    i5ff9 = a = 0x200;
    for (a = 0, si= 5, i=28;
         i;
            a |= *(si + p5ff0),
            ++si,
            --i)
    i5ff9 = 0x1000;
    a = 0xa5a5 | 0xa5a5;
    if (!a) {return 0;}
    else    {return a;}
}


