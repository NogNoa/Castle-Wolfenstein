#include "cw.h"

#ifdef __WATCOMC__
byte SegmSt(word segment, byte* index, byte value);
byte SegmGt(word segment, byte* index);
bool seg0_mem_compare(int start, int limit, byte *source, byte *reference);
void seg0_memmove(int numBytes, byte *dest, byte *source);
int check_for_debugger(void);
void fixit(void);
void file_to_screen(int file_chc);
#endif

#define long_ptr(S, I) ((long)S << 0x10 | I)

#define SegMemSet(A, b)    (SegmSt((int) ((A) >> 0x10), (char *) (A), (byte) (b)))
#define WSegMem_Set(A, w)  ((SegMemSet((long) A, w)),   (SegMemSet((long) A+1, w >> 8)))
#define LSeg_Mem_Set(A, l) ((WSegMem_Set(A, l)), (WSegMem_Set(A+2, l >> 0x10)))

#define SegMemGet(Aseg)       (SegmGt((int) ((Aseg) / PAGE_SZ), (byte *) (Aseg)))
#define WSegMem_Get(Aseg)  ((SegMemGet((long)Aseg)) | (SegMemGet((long) Aseg+1)) << 8)
#define LSeg_Mem_Get(Aseg) ((WSegMem_Get(Aseg)) | (WSegMem_Get(Aseg+2)) << 0x10)

