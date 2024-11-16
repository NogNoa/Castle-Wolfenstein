/* long_address_t* intTable(byte)*/
#define intTable(i) ((long) i*4)

#define SingleStep  intTable(1)
#define IntBreakpoint   intTable(3)
#define PrntScrn    intTable(5)
#define CtrlBreak   intTable(0x1B)
