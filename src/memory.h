#include "cw.h"

byte SegmSt(/*word segment, byte* index, byte value*/);
byte SegmGt(/*word segment, byte* index*/);
bool seg0_compare(/*int start, int limit, byte *source, byte *reference*/);
/*
void seg0_move(int numBytes, byte *dest, byte *source);
int check_for_debugger(void);
void fixit(void);
*/

#define long_ptr(S, I) ((long)S << 0x10 | I)

#define SegMemSet(A, b)    (SegmSt((int) ((A) / PAGE_SZ), (byte *) (A), (byte) (b)))
#define WSegMem_Set(A, w)  ((SegMemSet((long) A, w)),   (SegMemSet((long) A+1, w >> 8)))
#define LSeg_Mem_Set(A, l) ((WSegMem_Set(A, l)), (WSegMem_Set(A+2, l >> 0x10)))

#define SegMemGet(A)       (SegmGt((int) ((A) / PAGE_SZ), (byte *) (A)))
#define WSegMem_Get(A)  ((SegMemGet((long)A)) | (SegMemGet((long) A+1)) << 8)
#define LSeg_Mem_Get(A) ((WSegMem_Get(A)) | (WSegMem_Get(A+2)) << 0x10)


