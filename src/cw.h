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

#ifndef LATTICE
typedef char byte;
#endif

#ifndef NULL
#define NULL 0
#endif

#define PRODEBUG

#endif
