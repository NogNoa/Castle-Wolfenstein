#include "cw.h"
#include "IVT.h"
#include "memory.h"
#include "ibm.h"

long d7e = IntBreakpoint;
byte* default_drive = 0;
/*int goober_function(int p1, void* dest, register int si);*/

int inhibitInterrupts()
{
    if (WSegMem_Get(d7e) != 0x13cd) {return -1;}
    (((SegMemSet((long) CtrlBreak, 0x100003a0l)),
      (SegMemSet((long) CtrlBreak+1, 0x100003a0l >> 8))),
     ((SegMemSet((long) CtrlBreak+2, 0x100003a0l >> 0x10)),
      (SegMemSet((long) CtrlBreak+3, 0x100003a0l >> 0x18))));
    (((SegMemSet((long) PrntScrn, 0x100003a0l)),
      (SegMemSet((long) PrntScrn+1, 0x100003a0l >> 8))),
     ((SegMemSet((long) PrntScrn+2, 0x100003a0l >> 0x10)),
      (SegMemSet((long) PrntScrn+3, 0x100003a0l >> 0x18))));
    return 0;
}

static int d2ae, d29c;
bool pcjr;

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

int check_for_debugger()
{
    if (SegMemGet(IntBreakpoint+1) != 0xcd ||
        SegMemGet(SingleStep+1) != 0x13)
        {return _exit(-1), -1;} /*doesn't return*/
    else
    {   isDos210();
        return goober_function(0x26, 0x2bd, 0x40);
    }
}

int OnStack();

bool build_func_on_stack(arg)
{
  register int *bp;
  OnStack(arg);
  *(bp + 2) = 0x1000 & 0xff00;
  for (arg=1; arg < 8; ++arg)
  {   *(bp + (arg << 1) + 2) = 0;

  }
  return (*(bp + 2) == 0x1000);
}
