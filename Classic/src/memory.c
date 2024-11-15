#include "DOS.H"
#include "memory.h"
#include "ibm.h"
#include "video.h"
#include "IVT.h"
#include "console.h"
#include "STDLIB.H"

void
seg0_memmove(numBytes, dest, source)
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
    int i;
  
    for (i = start;
        i <= limit;
        ++i)
    {   val = SegMemGet((long)source + i); //from segment 0
        if (val != reference[i]) {return 0;}
    }
    return limit < i-start;
}

#define SP2D1 "\x8b\x26\xd1\2"
#define SS2d3 "\x8e\x16\xd3\2"

byte test_1a71[10]  = "\x2e" SP2D1 "\x2e" SS2d3; 
/*mov sp, word ptr cs:[0x2d1]   mov ss, word ptr cs:[0x2d3]*/
byte patch_1a71[10] = "\x2e" SS2d3 "\x2e" SP2D1;
/*mov ss, word ptr cs:[0x2d3]   mov sp, word ptr cs:[0x2d1]*/
byte test_22c2[10]  = "\x36" SP2D1 "\x36" SS2d3;
/*mov sp, word ptr ss:[0x2d1]   mov ss, word ptr ss:[0x2d3]*/
byte test_3ebd[8]  = SP2D1 SS2d3;
/*mov sp, word ptr [0x2d1]  mov ss, word ptr [0x2d3]*/
byte patch_3ebd[8] = SS2d3 SP2D1;
/*mov ss, word ptr [0x2d3]  mov sp, word ptr [0x2d1]*/
byte test_3fff[4]  = "\x8c\xc4\x8e\xd4";
/*mov sp, es    mov ss, sp*/
byte patch_3fff[4] = "\x8c\xc5\x8e\xd5";
/*mov bp, es    mov ss, bp*/

void
fixit()
{
    if (pcjr && isDos210())
    {   Seg0Assert(10, 0x1a71, test_1a71, patch_1a71);
        Seg0Assert(10, 0x22c2, test_22c2, patch_1a71);
        Seg0Assert(8, 0x3ebd, test_3ebd, patch_3ebd);
        Seg0Assert(4, 0x3fff, test_3fff, patch_3fff);
    }
    if (_seg_memset(0xb800, (byte*)1, 0xa5) != 0xa5) /*tryna to poke color screen buffer, is it there?*/
    {   setVideoMode(MDA);
        put_2_strings("Color graphics card not installed\n\r", "Program cannot execute");
        _exit(-1);
    }
    _seg_memset(0xb800, (byte*) 1, 0);
    SegMemSet(SingleStep+1, 0x34);
    SegMemSet(SingleStep+3, 0xff);
    _seg_memset(0x40, (byte*)0x10, _seg_memget(0x40, (byte*) 0x10) & 0xcf | 0x10);
    SegMemSet(IntBreakpoint+1, 0xcd);
    SegMemSet(IntBreakpoint+3, 0x13);
}


