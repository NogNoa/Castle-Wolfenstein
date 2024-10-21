#include "DOS.H"
#include "memory.h"

seg0_memmovee(numBytes, dest, source)
int numBytes;
byte *dest;
byte *source;
{   byte v;
    int i;
    for (i = 0; i <numBytes; i = i + 1) {
        v = source[i];
        _seg_memset(0, dest + i, v);
    }
}