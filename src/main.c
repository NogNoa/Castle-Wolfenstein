
#include "cw.h"

int d2ae, d29c;
extern bool pcjr;

#include "IVT.h"

void isPcJr(void)
{
  SegMemSet(SingleStep+1, 0x34);
  SegMemSet(SingleStep+3, 0xff);
  if (SegmGt(0xf000, (byte *)0xffff) == 0xfd) /* from the PC Jr BIOS*/
  { pcjr = true;
    d2ae = 900;
    d29c = 200;
  }
  else
  { pcjr = false;
    d2ae = 3300;
    d29c = 600;
  }
  SegMemSet(Breakpoint+1, 0xcd);
  SegMemSet(Breakpoint+3, 0x13);
}

int i9ec0, i9ec2;
byte a9ea0[0x20];

byte
olget9ea0()
{
    byte old;
    
    if (i9ec0 == i9ec2) {
        return 0;
    }
    old = a9ea0[i9ec0];
    a9ea0[i9ec0] = 0;
    i9ec0 = (i9ec0 + 1) % 0x20;
    return old;
}


byte
get_9ea0()
{
    return olget9ea0();
}

void 
fun728c()
{
    while (get_9ea0());
}


game()
{   puts("not nearly implemented");
}