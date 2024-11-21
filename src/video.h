#define SET_VIDEO_MODE 0
#define SET_CURSOR_POSITION 0x200
#define SET_BACKGROUND 0xb00

/* int RowColl(byte row, byte coll); */
#define RowColl(row, coll) (((row) - 1) << 8 | ((coll) - 1))


/*video modes*/
#define TXT_GREY_WD  0
#define TXT_CLR_WD   1
#define TXT_GREY_THN 2
#define TXT_CLR_THN  3
#define PXL_CLR_LO   4
#define PXL_GREY_HI  5
#define PXL_MONO_HI  6
#define MDA          7
#define JR_TINY      8
#define JR_WIDE      9

/*CGA Colours*/ 
#define CGA_BLUE         1
/* int setVideoMode(char mode_p);
void BiosVideo(int A, int B, int C, int D);*/

#define DISPLAY_BUFFER 0xb800
