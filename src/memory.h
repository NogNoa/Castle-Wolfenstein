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

#define SegMemSet(Aseg, bval)    (SegmSt((int) ((Aseg) / PAGE_SZ), (byte *) (Aseg), (byte) (bval)))
#define WSegMem_Set(Aseg, w)  ((SegMemSet((long) Aseg, w)),   (SegMemSet((long) Aseg+1, w >> 8)))
#define LSeg_Mem_Set(Aseg, l) ((WSegMem_Set(Aseg, l)), (WSegMem_Set(Aseg+2, l >> 0x10)))

#define SegMemGet(Aseg)       (SegmGt((int) ((Aseg) / PAGE_SZ), (byte *) (Aseg)))
#define WSegMem_Get(Aseg)  ((SegMemGet((long)Aseg)) | (SegMemGet((long) Aseg+1)) << 8)
#define LSeg_Mem_Get(Aseg) ((WSegMem_Get(Aseg)) | (WSegMem_Get(Aseg+2)) << 0x10)


