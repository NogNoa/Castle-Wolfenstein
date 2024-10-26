#include "DOS.H"
#include "memory.h"
#include "ibm.h"
#include "video.h"

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

byte test_1a71[10]  = "\x2e\x8b\x26\xd1\2\x2e\x8e\x16\xd3\2";
byte patch_1a71[10] = "\x2e\x8e\x16\xd3\2\x2e\x8b\x26\xd1\2";
byte test_22c2[10]  = "\x36\x8b\x26\xd1\2\x36\x8e\x16\xd3\2";
byte test_3ebd[8]  = "\x8b\x26\xd1\2\x8e\x16\xd3\2";
byte patch_3ebd[8] = "\x8e\x16\xd3\2\x8b\x26\xd1\2";
byte test_3fff[4]  = "\x8c\xc4\x8e\xd4";
byte patch_3fff[4] = "\x8c\xc5\x8e\xd5";

/*void*/
setup_memory()
{
    if (pcjr && isDos210())
    {   Seg0Assert(9, (byte *)0x1a71, (byte *)test_1a71, (byte *)patch_1a71);
        Seg0Assert(9, (byte *)0x22c2, (byte *)test_22c2, (byte *)patch_1a71);
        Seg0Assert(7, (byte *)0x3ebd, (byte *)test_3ebd, (byte *)patch_3ebd);
        Seg0Assert(3, (byte *)0x3fff, (byte *)test_3fff, (byte *)patch_3fff);
    }
    if (_seg_memset(0xb800, 1, 0xa5) != 0xa5) /*tryna to poke color screen buffer, is it there?*/
    {   setVideoMode(MDA);
        put_2_lines("Color graphics card not installed\n\r", "Program cannot execute");
        _exit(-1);
    }
    _seg_memset(0xb800, 1, 0);
    _seg_memset(0, 5, 34);
    _seg_memset(0, 7, 0xff);
    _seg_memset(0x40, 0x10, _seg_memget(0x40, 0x10) & 0xcf | 0x10);
    _seg_memset(0, 0xd, 0xcd);
    _seg_memset(0, 0xf, 0x13);
}
