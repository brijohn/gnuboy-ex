
#ifndef _STDLIB_H
#define _STDLIB_H

#include "../memmgr.h"

#define NULL 0


#define malloc memmgr_alloc
#define realloc memmgr_realloc
#define free memmgr_free

int rand(void);
void srand(unsigned int seed);

int atoi(const char *s);

void _Exit(int status);
#define exit(x) _Exit(-2)

#endif // _STDLIB_H
