#ifndef PROG_CW
#define PROG_CW

typedef char * string;
typedef unsigned int uint;

typedef char bool;
enum {false, true};

#ifndef LATTICE
typedef char byte;
int sum(int *list, int len);
#else
typedef int void;
#endif

#ifndef NULL
#define NULL 0
#endif



#endif