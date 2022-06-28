#ifndef ALUMNOS_H_INCLUDED
#define ALUMNOS_H_INCLUDED
#include <stdlib.h>

#define BIGFILENAME        "Cliente.dat"
#define INDEXFILE          "Clientes.idx"
#define INDEXFILEINORDEN   "ClientesINORDEN.idx"

typedef struct{
    unsigned key;
    char deleted;
    char value[100];
}tdat;

typedef struct{
    unsigned key;
    unsigned aux;
    size_t position;
}tidx;


int createBigFile(const char* filename, unsigned asize);

int shuffleFile(const char* filename, size_t recordsize);





#endif // ALUMNOS_H_INCLUDED
