#include "video.h"
#include "conio.h"

static char f1, ee;
static char Rank_Index;

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
