#define SET_CURSOR_POSITION 0x200

int RowColl(/* byte row, byte coll*/);
#define RowColl(row, coll) (((row) - 1) << 8 | ((coll) - 1))

enum VIDEO_MODES {TXT_GREY_WD, TXT_CLR_WD, TXT_GREY_THN, TXT_CLR_THN, 
                  PXL_CLR_LO, PXL_GREY_HI, PXL_MONO_HI, MDA, 
                  JR_TINY, JR_WIDE};

#ifndef LATTICE
extern int setVideoMode(char mode_p);
extern void BiosVideo(int A, int B, int C, int D);
#endif
