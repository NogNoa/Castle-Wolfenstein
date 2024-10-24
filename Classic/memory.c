#include "DOS.H"
#include "memory.h"

/*void*/
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


bool seg0_mem_compare(start,limit,source,reference)
int start, limit;
byte *source, *reference;
{
    byte val;
    int similar, i;
  
    for (similar = 0, i = similar + start;
        similar <= limit - start;
        ++similar, ++i)
    {   val = SegMemGet(source + i); //from segment 0
        if (val != reference[i]) {return 0;}
    }
    return limit < similar;
}
