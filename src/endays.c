
#include "cw.h"

int strt_9ea0, stop_9ea0;
byte a9ea0[0x20];

void 
fun728c()
{
    while (get_9ea0());
}


byte
get_9ea0()
{
    return olget9ea0();
}

byte
olget9ea0()
{
    byte back;
    
    if (strt_9ea0 == stop_9ea0) {
        return 0;
    }
    back = a9ea0[strt_9ea0];
    a9ea0[strt_9ea0++] = 0;
    strt_9ea0 %= 0x20;
    return back;
}

void
set_9ea0(call)
byte call;
{
  a9ea0[stop_9ea0++] = call;
  stop_9ea0 %= 0x20;
}

game()
{   puts("not nearly implemented");
}