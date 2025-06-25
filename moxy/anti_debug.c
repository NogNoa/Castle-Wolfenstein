#include "cw.h"
#include "IVT.h"
#include "memory.h"

long d7e = Breakpoint;
byte* default_drive = 0;

#ifdef __WATCOMC__
#include "conio.h"

#endif

int inhibitInterrupts(void)
{
    int intbrk = WSegMem_Get(d7e);
    if (intbrk != 0x13cd) 
      { cprintf("\n%x\n", intbrk);
        return -1;
      }
    LSeg_Mem_Set(CtrlBreak, 0x100003a0l);
    LSeg_Mem_Set(PrntScrn,  0x100003a0l);
    return 0;
}
