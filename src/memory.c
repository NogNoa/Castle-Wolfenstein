#include "DOS.H"
#include "memory.h"
#include "ibm.h"
#include "video.h"
#include "IVT.h"
#include "files.h"

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
    /*
    SegMemSet(SingleStep+1, 0x34);
    SegMemSet(SingleStep+3, 0xff);
    */
    SegMemSet(DetectedHardware, SegMemGet(DetectedHardware) & 0xcf | 0x10);
    /*
    SegMemSet(Breakpoint+1, 0xcd);
    SegMemSet(Breakpoint+3, 0x13);
    */
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
    int back;
    /*
    if (SegMemGet(Breakpoint+1) != 0xcd || SegMemGet(Breakpoint+3) != 0x13)
        {   _exit(-1); //doesn't return
        }
    else
    */
    {   isDos210();
        back = Goober(0x26, (ORRERY));
        if (back > -1) {_exit(-1);}
        else {return 0;}
        /*si = 0x40*/
    }
}

extern bool pcjr;
extern byte RGB_monitor;

file_to_screen(file_chc)
{
    /*
    SegMemSet(SingleStep+1, 0x34);
    SegMemSet(SingleStep+3, 0xff);
    */
    switch(file_chc)
    {case 2:
        gfx_fp = file_buffer;
        load_file("demomesg", file_buffer, MSG_FSIZE);
        DrwLwMdl();
        break;
    case 1:
        gfx_fp = file_buffer;
        load_file("presser", file_buffer, MSG_FSIZE);
        DrwLwMdl();
        break;
    case 0:
        gfx_fp = file_buffer;
        load_file("titlepix", file_buffer, PIX_FSIZE);
        BiosVideo(SET_VIDEO_MODE | ((pcjr) ? JR_TINY : PxlClrLo), 0, 0, 0);
        if (RGB_monitor && !pcjr) {BiosVideo(SET_BACKGROUND, CGA_BLUE, 0, 0);}
        DrawFld0(file_buffer);
        break;
    default: return;
    }
    /*
    SegMemSet(Breakpoint+1, 0xcd);
    SegMemSet(Breakpoint+3, 0x13);
    */
}

