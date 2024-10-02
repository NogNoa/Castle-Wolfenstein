fun_8e2d(char* call)
{
    int local[0x1B];
    local[0x13] = -1;
    local[0x12] == 0x20;
    local[0x16] = local[0x11] = local[0x15] = local[0x14] = 0;
    if (*call == 0x2d)
    {
        ++call;
        local[0x16] = 1;
    }
    int si, di, ax;
    char al, bvar1, bl;
    local[0] = *call;
    bvar1 = *(char *)((*call) + 0xa0b5);
    if (bvar1 & 4 != 0 && local[0] == 0x30)
        {local[0x12] = 0x30;}
    for (;bvar1 & 4 != 0; bvar1 = *(char *)(*call + 0xa0b5))
    {   local[0x11] *= 0xa;
        local[0x11] += (*call & 0xf);
        ++call;
    }
}

char f1, ee;
signed char Rank_Index;

signed char rank_calculate(void)
{
  char bVar1;
  
  if (f1 < 0x80) {
    if (1 < f1) {
      Rank_Index -= 1;
    }
  }
  else {
    if (-0x10 > Rank_Index || Rank_Index > -1) 
    {   Rank_Index += 0x10;
        if (ee && (-0x10 > Rank_Index || Rank_Index > -1))
            {Rank_Index += 0x10;}
    }
    if ((-0x11 < Rank_Index && Rank_Index < 0)) {
      Rank_Index = -0x10;
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

char *rank_area_top=0x91b0;
void Rank_print(signed char Rank_Index)
{
  Set_Video_mode(4);
  BIOS_Video(0x200,0,0,0x100);
  puts("Your Rank is ");
  puts(*(char **)(rank_area_top + ((int)Rank_Index >> 5) * 2));
  return;
}
Rank_print(-0x10) {0x91b0 + (0xf0 >> 5) << 1} = {0x91b0 + (0xff ) << 1} = {0x91b0 + 0xfe} = {0x91b0 + -2} = {0x90ae} =
Rank_print(0x10) {0x91b0 + (0x10 >> 5) << 1} = {0x91b0 + (0) << 1} = 0x91b0
