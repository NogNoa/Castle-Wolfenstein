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

#define SegMemSet(Aseg, bval)    (SegmSt((int) ((Aseg) >> 0x10), (char *) (Aseg), (byte) (bval)))
#define WSegMem_Set(Aseg, wval)  ((SegMemSet((long) Aseg, wval)),   (SegMemSet((long) Aseg+1, wval >> 8)))
#define LSeg_Mem_Set(Aseg, lval) ((WSegMem_Set(Aseg, lval)), (WSegMem_Set(Aseg+2, lval >> 0x10)))

#define SegMemGet(Aseg)       (SegmGt((int) ((Aseg) / PAGE_SZ), (byte *) (Aseg)))
#define WSegMem_Get(Aseg)  ((SegMemGet((long)Aseg)) | (SegMemGet((long) Aseg+1)) << 8)
#define LSeg_Mem_Get(Aseg) ((WSegMem_Get(Aseg)) | (WSegMem_Get(Aseg+2)) << 0x10)

