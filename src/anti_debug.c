#include "cw.h"
#include "IVT.h"
#include "memory.h"
#include "STDLIB.H"
#include "ibm.h"

long d7e = IntBreakpoint;
byte* default_drive = 0;
int _Goober(int p1, void* dest);

int inhibitInterrupts()
{
    if (WSegMem_Get(d7e) != 0x13cd) {return -1;}
    LSeg_Mem_Set(CtrlBreak, 0x100003a0l);
    LSeg_Mem_Set(PrntScrn,  0x100003a0l);
    return 0;
}

static int d2ae, d29c;
bool pcjr;

void isPcJr()
{
  SegMemSet(SingleStep+1, 0x34);
  SegMemSet(SingleStep+3, 0xff);
  pcjr = (_seg_memget(0xf000, (char *)0xffff) == 0xfd); /* from the PC Jr BIOS*/
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

extern void *orrery;

int check_for_debugger()
{
    if (SegMemGet(IntBreakpoint+1) != 0xcd ||
        SegMemGet(SingleStep+1) != 0x13)
        {return _exit(-1), -1;} /*doesn't return*/
    else
    {   isDos210();
        return _Goober(0x26, orrery); 
        /*si = 0x40*/
    }
}

int CallStack();

bool build_func_on_stack(int arg)
{
  int fnstk[8];
  fnstk[0] = 0x1b8;
  fnstk[1] = 0xbb02;
  fnstk[2] = 0x7c62;
  fnstk[3] = 0x1b8;
  fnstk[4] = arg + 0xba00;
  fnstk[5] = *default_drive;
  fnstk[6] = 0x9090;
  fnstk[7] = 0xcb;
  CallStack();
  fnstk[0] = 0x1000;
  for (arg=1; arg < 8; ++arg)
  {     fnstk[arg] = 0;

  }
  return (fnstk[0] == 0x1000);
}
