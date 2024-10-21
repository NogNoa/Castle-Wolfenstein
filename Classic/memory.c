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
    bool back;
    byte val;
    int similar;
    int i;
  
    similar = back = 0;
    for (i = start; i <= limit; ++i) 
    {   val = SegMemGet(source + i); //from segment 0
        if (val == reference[i]) 
        {    ++similar;
        }
        else 
        {   back = true;
        }
    }
    if ((limit < similar) && (!back)) 
    {    return 0x1;
    }
    return 0x0;
}
