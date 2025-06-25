#include "cw.h"

#ifdef __WATCOMC__
void isPcJr(void);
int inhibitInterrupts(void);
int check_for_debugger(void);
#endif

extern byte* dflt_drv;
extern bool pcjr;
