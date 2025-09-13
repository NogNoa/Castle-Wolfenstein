
#include "cw.h"

int i9ec0, i9ec2;
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
    byte old;
    
    if (i9ec0 == i9ec2) {
        return 0;
    }
    old = a9ea0[i9ec0];
    a9ea0[i9ec0] = 0;
    i9ec0 = (i9ec0 + 1) % 0x20;
    return old;
}


game()
{   puts("not nearly implemented");
}