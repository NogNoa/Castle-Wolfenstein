/*BiosVideo functions*/
#define SET_VIDEO_MODE 0
#define SET_CURSOR_POSITION 0x200
#define WRITE_CHAR_COLOR 0x900
#define SET_PAL_BG_BRDR 0xb00

#define PAL_RGY 0x100

#ifdef __WATCOMC__
int setVideoMode(char mode_p);
void BiosVideo(int A, int B, int C, int D);
#endif

/* int RowColl(char row, char coll); */
#define RowColl(row, coll) ((int) ((row) - 1) << 8 | ((coll) - 1))


/*video modes*/
#define TxtGreyWd  0
#define TxtClrWd   1
#define TxtGreyThn 2
#define TXT_CLR_THN  3
#define PxlClrLo   4
#define PXL_GREY_HI  5
#define PXL_MONO_HI  6
#define MDA          7
#define JR_TINY      8
#define JR_WIDE      9

/*Text Mode Colors*/
#define BlackFG 0
#define BlueFG 1
#define GreenFG 2
#define CyanFG 3
#define RedFG 4
#define MagentaFG 5
#define BrownFG 6
#define GreyFG 7
#define BrightFG 8
#define YellowFG (BrownFG | BrightFG)
#define WhiteFG (GreyFG | BrightFG)


/*CGA Colours*/ 
#define CGA_BLUE         1

#define DISPLAY_BUFFER 0xb800

#define PositCPuts(row, coll, str) (BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl((row), (coll))), \
                    cputs(str))
#define PositCPrintf(row, coll, format, var) (BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl((row), (coll))), \
                    cprintf(format, var))
