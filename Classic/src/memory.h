#include "cw.h"

byte _seg_memset(word, byte*, byte);
byte _seg_memget(word, byte*);
       bool seg0_mem_compare(int start, int limit, byte *source, byte *reference);
#ifndef LATTICE
void seg0_memmovee(int numBytes, byte *dest, byte *source);
int check_for_debugger(void);
void setup_memory(void);
#endif

#define SegMemSet(A, b)    (_seg_memset((int) ((A) >> 0x10), (char *) (A), (byte) (b)))
#define WSegMem_Set(A, w)  {(SegMemSet((long) A, w));   (SegMemSet((long) A+1, w >> 8));}
#define LSeg_Mem_Set(A, l) {{WSegMem_Set(A, l)} {WSegMem_Set(A+2, l >> 0x10)}}

#define SegMemGet(A)       (_seg_memget((int) ((A) >> 0x10), (char *) (A)))
#define WSegMem_Get(A)  ((SegMemGet((long)A)) + (SegMemGet((long) A+1)) * 0x100)
#define LSeg_Mem_Get(A) ((WSegMem_Get(A)) + (WSegMem_Get(A+2)) * 0x10000)

#define Seg0Assert(lmt, cur, ref, fix) {if (seg0_mem_compare(0, (lmt)-1, (byte *) (cur), (byte *) (ref)))\
{seg0_memmovee((lmt), (byte *) (cur), (byte *) (fix));}}


