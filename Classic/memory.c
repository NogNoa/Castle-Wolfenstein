#include "DOS.H"

extern byte seg_memset();

void seg0_memmovee(numBytes, dest, source)
int numBytes;
byte *dest;
byte *source;
{   byte v;
    int i;
    for (i = 0; i <numBytes; i = i + 1) {
        v = source[i];
        seg_memset(0, dest + i, v);
    }
}