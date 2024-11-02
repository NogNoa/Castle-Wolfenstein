#include "cw.h"

extern byte _seg_memset();
extern byte _seg_memget();
       bool seg0_mem_compare();
/*  byte _seg_memset(word, byte*, byte)
    byte _seg_memget(word, byte*)
    void seg0_memmovee(int numBytes, byte *dest, byte *source)
    bool seg0_mem_compare(int start, int limit, byte *source, byte *reference)
*/

#define SegMemSet(A, b)    (_seg_memset((int) (A) >> 0x10, (char *) (A), (byte) b))
#define WSegMem_Set(A, w)  {(SegMemSet(A, w));   (SegMemSet(A+1, w>>8));}
#define LSeg_Mem_Set(A, l) {{WSegMem_Set(A, l)} {WSegMem_Set(A+2, l>>0x10)}}

#define SegMemGet(A)       (_seg_memget((int) (A) >> 0x10, (char *) (A)))
#define WSegMem_Get(A)  ((SegMemGet(A)) + (SegMemGet(A+1)) * 0x100)
#define LSeg_Mem_Get(A) ((WSegMem_Get(A)) + (WSegMem_Get(A+2)) * 0x10000)

#define Seg0Assert(lmt, cur, ref, fix) {if (seg0_mem_compare(0, (lmt)-1, (cur), (ref)))\
{seg0_memmovee((lmt), (cur), (fix));}}
