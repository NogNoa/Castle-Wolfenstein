#ifndef PROG_CW
#define PROG_CW

typedef char * string;
typedef unsigned int uint;

typedef char bool;
enum {false, true};

#ifndef LATTICE
typedef char byte;
#endif

#ifndef NULL
#define NULL 0
#endif

int sum(int *list, int len);

#endif