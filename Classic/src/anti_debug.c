#include "cw.h"
#include "IVT.h"
#include "memory.h"
#include "STDLIB.H"
#include "ibm.h"

long d7e = IntBreakpoint;
byte* default_drive = 0;
int goober_function(int p1, void* dest);

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

int check_for_debugger()
{
    if (SegMemGet(IntBreakpoint+1) != 0xcd ||
        SegMemGet(SingleStep+1) != 0x13)
        {return _exit(-1), -1;} /*doesn't return*/
    else
    {   isDos210();
        return goober_function(0x26, 0x2bd); 
        /*si = 0x40
        0x2bd is the address of build_func_on_stack + 1f
        not clear how to represent that or even reliably
        get the value in c.
        both check_for_debugger and build_func_on_stack 
        bear the marks of mcc 1.04
        */
    }
}
