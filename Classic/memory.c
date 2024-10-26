#include "DOS.H"
#include "memory.h"
#include "ibm.h"

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
        i <= limit;
        ++similar, ++i)
    {   val = SegMemGet(source + i); //from segment 0
        if (val != reference[i]) {return 0;}
    }
    return limit < similar;
}

byte dc[10] = "\x2e\x8b\x26\xd1\2\x2e\x8e\x16\xd3\2";

/*void*/
setup_memory()
{
    if (pcjr && isDos210())
    {   if (seg0_mem_compare(0, 9, (byte *)0x1a71  ,(byte *)dc))
        {seg0_memmovee}

    }
}
