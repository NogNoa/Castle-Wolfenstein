#include "cw.h"
#include "anti_debug.h"
#include "IVT.h"
int OnStack(int);

bool build_func_on_stack(int arg)
{
  register int *bp;
  OnStack(arg);
  *(bp + 2) = 0x1000 & 0xff00;
  for (arg=1; arg < 8; ++arg)
  {   *(bp + (arg << 1) + 2) = 0;

  }
  return (*(bp + 2) == 0x1000);
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
