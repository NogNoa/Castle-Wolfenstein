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
  
    similar = 0;
    for (i = start; i <= limit; ++i) 
    {   val = SegMemGet(source + i); //from segment 0
        if (val == reference[i]) 
        {    ++similar;
        }
        else {return 0;}
    }
    if (limit < similar) {return 1;}
     else {return 0;}
}
