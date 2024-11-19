#include "DOS.H"
#include "memory.h"
#include "ibm.h"
#include "video.h"
#include "IVT.h"

seg0_move(numBytes, dest, source)
int numBytes;
byte *dest;
byte *source;
{   int i;
    byte v;
    for (i = 0; i <numBytes; i = i + 1) {
        v = source[i];
        SegmSt(0, dest + i, v);
    }
}

byte test_1a71[10]  = "\x2e\x8b\x26\xd1\2\x2e\x8e\x16\xd3\2";
byte patch_1a71[10] = "\x2e\x8e\x16\xd3\2\x2e\x8b\x26\xd1\2";
byte test_22c2[10]  = "\x36\x8b\x26\xd1\2\x36\x8e\x16\xd3\2";
byte test_3ebd[8]  = "\x8b\x26\xd1\2\x8e\x16\xd3\2";
byte patch_3ebd[8] = "\x8e\x16\xd3\2\x8b\x26\xd1\2";
byte test_3fff[4]  = "\x8c\xc4\x8e\xd4";
byte patch_3fff[4] = "\x8c\xc5\x8e\xd5";

#define CGA_Space 0xb800
#define DetectedHardware 0x400010l

fixit()
{
    byte p;
    if (pcjr && isDos210())
    {   if (seg0_compare(0, (10)-1, (byte *) (0x1a71), (byte *) (test_1a71)))
            {seg0_move((10), (byte *) (0x1a71), (byte *) (patch_1a71));}
        if (seg0_compare(0, (10)-1, (byte *) (0x22c2), (byte *) (test_22c2)))
            {seg0_move((10), (byte *) (0x22c2), (byte *) (patch_1a71));}
        if (seg0_compare(0, (8)-1, (byte *) (0x3ebd), (byte *) (test_3ebd)))
            {seg0_move((8), (byte *) (0x3ebd), (byte *) (patch_3ebd));};
        if (seg0_compare(0, (4)-1, (byte *) (0x3fff), (byte *) (test_3fff)))
            {seg0_move((4), (byte *) (0x3fff), (byte *) (patch_3fff));}
    }
    if (SegmSt(CGA_Space, (byte*)1, 0xa5) != 0xa5) /*tryna to poke color screen buffer, is it there?*/
    {   setVideoMode(MDA);
        put_2_strings("Color graphics card not installed\n\r", "Program cannot execute");
        _exit(-1);
    }
    SegmSt(CGA_Space, (byte*) 1, 0);
    SegMemSet(SingleStep+1, 0x34);
    SegMemSet(SingleStep+3, 0xff);
    SegMemSet(DetectedHardware, SegMemGet(DetectedHardware) & 0xcf | 0x10);
    SegMemSet(IntBreakpoint+1, 0xcd);
    SegMemSet(IntBreakpoint+3, 0x13);
}

bool seg0_compare(start,limit,source,reference)
int start, limit;
byte *source;
byte *reference;
{
    byte val;
    int i;
  
    for (i = start;
        i <= limit;
        ++i)
    {   val = SegMemGet((long)source + i); /*from segment 0*/
        if (val != reference[i]) {return 0;}
    }
    return limit < i-start;
}

extern byte* dflt_drv;

bool build_func_on_stack(arg)
{
  int fnstk[8];
  fnstk[0] = 0x1b8;
  fnstk[1] = 0xbb02;
  fnstk[2] = 0x7c62;
  fnstk[3] = 0x1b8;
  fnstk[4] = arg + 0xba00;
  fnstk[5] = *dflt_drv;
  fnstk[6] = 0x9090;
  fnstk[7] = 0xcb;
  CallStck();
  fnstk[0] = 0x1000;
  for (arg=1; arg < 8; ++arg)
  {     fnstk[arg] = 0;

  }
  return (fnstk[0] == 0x1000);
}

#define ORRERY (&build_func_on_stack + 0x1F)

int check_for_debugger()
{
    if (SegMemGet(IntBreakpoint+1) != 0xcd ||
        SegMemGet(SingleStep+1) != 0x13)
        {return _exit(-1), -1;} /*doesn't return*/
    else
    {   isDos210();
        return Goober(0x26, (ORRERY));
        /*si = 0x40*/
    }
}

long int_frust_p = IntBreakpoint;

int inhibitInterrupts()
{
    if (WSegMem_Get(int_frust_p) != 0x13cd) {return -1;}
    (((SegMemSet((long) CtrlBreak, 0x100003a0l)),
      (SegMemSet((long) CtrlBreak+1, 0x100003a0l >> 8))),
     ((SegMemSet((long) CtrlBreak+2, 0x100003a0l >> 0x10)),
      (SegMemSet((long) CtrlBreak+3, 0x100003a0l >> 0x18))));
    (((SegMemSet((long) PrntScrn, 0x100003a0l)),
      (SegMemSet((long) PrntScrn+1, 0x100003a0l >> 8))),
     ((SegMemSet((long) PrntScrn+2, 0x100003a0l >> 0x10)),
      (SegMemSet((long) PrntScrn+3, 0x100003a0l >> 0x18))));
    return 0;
}