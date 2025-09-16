
#include "cw.h"

int qstart, qstop;
byte queue[0x20];

void 
clear_queue()
{
    while (qpull());
}


byte
qpull()
{
    return olqpull();
}

byte
olqpull()
{
    byte back;
    
    if (qstart == qstop) {
        return 0;
    }
    back = queue[qstart];
    queue[qstart++] = 0;
    qstart %= 0x20;
    return back;
}

void
qpush(call)
byte call;
{
  queue[qstop++] = call;
  qstop %= 0x20;
}

void
qpara_push(call)
uint call;
{
  call &= 0xf;
  if (call > 4){ vall >>= 2;}
  qpush((byte)call);
}

game()
{   puts("not nearly implemented");
}