#include "cw.h"
#include "IVT.h"
#include "ibm.h"
#include "memory.h"
#include "video.h"
#include "conio.h"

char cl;
short si;
extern char ascii_flags[];

void _pfmt(char* format_type)
{
    int local[0x1B];
    char bvar1;
    local[0x13] = -1;
    local[0x12] = 0x20;
    local[0x16] = local[0x11] = local[0x15] = local[0x14] = 0;
    if (*format_type == 0x2d)
    {
        ++format_type;
        local[0x16] = 1;
    }
    local[0] = *format_type;
    bvar1 = ascii_flags[(int)*format_type];
    if (bvar1 & 4 != 0 && local[0] == 0x30)
        {local[0x12] = 0x30;}
    for (;bvar1 & 4 != 0; bvar1 = *(char *)(*format_type + 0xa0b5))
    {   local[0x11] *= 0xa;
        local[0x11] += (*format_type & 0xf);
        ++format_type;
    }
}

char f1, ee;
char Rank_Index;

char rank_calculate(void)
{
  
  if (f1 < 0x80) {
    if (1 < f1) {
      Rank_Index -= 1;
    }
  }
  else {
    if (Rank_Index <= 0xf0) 
    {   Rank_Index += 0x10;
        if (ee && (Rank_Index <= 0xf0))
            {Rank_Index += 0x10;}
    }
    if ((0xf0 < Rank_Index)) {
      Rank_Index = 0xf0;
    }
  }
  if (Rank_Index < 0x10) {
    Rank_Index = 0x10;
  }
  return Rank_Index;
}
  /*     100 > ur >=  f0
          00 > sr >= -10
  
  */

char *rank_table[8];
void Rank_print(char Rank_Index)
{
    setVideoMode(4);
    BiosVideo(0x200,0,0,0x100);
    cputs("Your Rank is ");
    cputs(rank_table[(int)Rank_Index >> 5]);
    return;
}

long d7e = IntBreakpoint;
byte seg_memget();

int inhibitInterrupts()
{
    if (WSegMem_Get(d7e) != 0x13cd) {return -1;}
    LSeg_Mem_Set(CtrlBreak, 0x100003a0);
    LSeg_Mem_Set(PrntScrn,  0x100003a0);
    return 0;
}

int d2ae, d29c; 

void isPcJr()
{
  SegMem_Set(SingleStep+1, 0x34);
  SegMem_Set(SingleStep+3, 0xff);
  pcjr = (_seg_memget(0xf000, 0xffff) == 0xfd); /* from the PC Jr BIOS*/
  if (pcjr)
  { d2ae = 3300;
    d29c = 600;
  }
  else
  { d2ae = 900;
    d29c = 200;
  }
  SegMem_Set(IntBreakpoint+1, 0xcd);
  SegMem_Set(IntBreakpoint+3, 0x13);
}
