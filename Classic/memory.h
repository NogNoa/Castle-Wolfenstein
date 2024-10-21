#include "cw.h"

extern byte _seg_memset();
extern byte _seg_memget();
/* void seg0_memmovee(int numBytes, byte *dest, byte *source)
*/

#define SegMemSet(A, b)    (_seg_memset((int) (A) >> 0x10, (char *) (A), (byte) b))
#define WSegMem_Set(A, w)  ((SegMemSet(A, w));   (SegMemSet(A+1, w>>8)))
#define LSeg_Mem_Set(A, l) ((WSegMem_Set(A, l)); (WSegMem_Set(A+2, l>>0x10)))

#define SegMemGet(A)       (_seg_memset((int) (A) >> 0x10, (char *) (A)))
#define WSegMem_Get(A)  ((SegMemGet(A)) + (SegMemGet(A+1)) * 0x100)
#define LSeg_Mem_Get(A) ((WSegMem_Get(A)) + (WSegMem_Get(A+2)) * 0x10000)