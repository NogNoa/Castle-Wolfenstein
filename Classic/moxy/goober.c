#include "cw.h"
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