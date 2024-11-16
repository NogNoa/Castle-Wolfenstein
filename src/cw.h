#ifndef PROG_CW
#define PROG_CW

typedef char * string;
typedef unsigned int uint;
typedef unsigned int word;

typedef char bool;
enum {false, true};

#ifndef LATTICE
typedef unsigned char byte;
#endif

int sum(int *list, int len);

#ifndef NULL
#define NULL 0
#endif

#endif
