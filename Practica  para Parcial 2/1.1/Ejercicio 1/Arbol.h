#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#define DUPLICADO 2

typedef struct sNodoArbol{
void* info;
unsigned tamInfo;
struct sNodoArbol* izq;
struct sNodoArbol* der;
}tNodoArbol;

typedef tNodoArbol* tArbol;


void crearArbol(tArbol* arbol);

int insertarEnArbolRec(tArbol* arbol, void* dato, unsigned cantBytes, int(*cmpDni)(const void*, const void*));

void vacairArbol(tArbol* arbol);



#endif // ARBOL_H_INCLUDED
