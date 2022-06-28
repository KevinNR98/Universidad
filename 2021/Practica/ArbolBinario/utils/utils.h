#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdlib.h>

typedef struct{
    unsigned key;
    char deleted;
    char value[128];
}tdat;

typedef struct{
    unsigned key;
    unsigned aux;
    size_t position;
}tidx;



int createBigFile(const char* filename, unsigned asize);
int shuffleFile(const char* filename, size_t recordsize);

#endif // UTILS_H_INCLUDED
