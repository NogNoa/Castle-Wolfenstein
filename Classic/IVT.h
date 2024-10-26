// long_address_t* intTable(byte)
#define intTable(i) (i*4)

#define IntBreakpoint intTable(3)
#define CtrlBreak intTable(0x1B)
#define PrntScrn intTable(5)