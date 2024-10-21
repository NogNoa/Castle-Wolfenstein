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


bool mem_compare(int start,int limit,byte *source,byte *reference)
{
    byte val;
    int similar;
    int i;
  
    for (i = 0; i <= limit - start; ++i) 
    {   val = SegMemGet(source + i + start); //from segment 0
        if (val != reference[i + start]) {return 0;}
    }
    if (limit < i) {return 1;}
     else {return 0;}
}
