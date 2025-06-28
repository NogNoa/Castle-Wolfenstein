#ifndef PROG_CW
#define PROG_CW
typedef char * string;
typedef unsigned int uint;
typedef unsigned int word;
typedef int signed_error;

typedef char bool;
#define false 0
#define true 1

#define PAGE_SZ 0x100

#ifndef __WATCOMC__
#define void
#define inline

#else
#include "STDLIB.H";
int sum(int *list, int len);
#endif /* __WATCOMC__ */

#ifndef LATTICE
typedef char byte;
#endif /* LATTICE */

#ifndef NULL
#define NULL 0
#endif /* NULL */

#define PRODEBUG

#define CTRL(c) (0x40^c)
#define ESC (0x40^'[')

#endif /* PROG_CW */ 

