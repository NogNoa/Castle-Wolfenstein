#define SET_CURSOR_POSITION 0x200

/* int row_coll(byte row, byte coll) */
#define RowColl(row, coll) (((row) - 1) << 8 | ((coll) - 1))

enum VIDEO_MODES {TXT_GREY_WD, TXT_CLR_WD, TXT_GREY_THN, TXT_CLR_THN, 
                  PXL_CLR_LO, PXL_GREY_HI, PXL_MONO_HI, MDA, 
                  JR_TINY, JR_WIDE};

/* extern int set_video_mode(byte)*/
/* extern void BiosVideo(int, int, int, int))*/

