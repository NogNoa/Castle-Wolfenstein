
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

game()
{   puts("not nearly implemented");
}