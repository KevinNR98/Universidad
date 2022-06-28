#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#define DUPLICADO 2
#include "funciones.h"

typedef struct SnodoArb{
void* info;
unsigned tamInfo;
struct SnodoArb* izq;
struct SnodoArb* der;
}tNodoArbol;

typedef tNodoArbol* tArbol;

void crearArbol(tArbol* arbol);

int insertarEnArbolRec(tArbol* arbol, void* dato, unsigned cantBytes, int(*comparar)(const void*, const void*));

#endif // ARBOL_H_INCLUDED
