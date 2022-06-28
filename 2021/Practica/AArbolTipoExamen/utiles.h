#ifndef UTILES_H_INCLUDED
#define UTILES_H_INCLUDED
#include "../../../Librerias/Arbol.h"

int cargarIndice(tArbol* arbol, const char* filename, int(*comparar)(const void*, const void*));

int cargarIndiceArchInOrd(tArbol* arbol, int(*comparar)(const void*, const void*));

int cargarIdxArchInOrd_R(tArbol* arbol, int li, int ls, FILE* arch, int(*comparar)(const void*, const void*));

#endif // UTILES_H_INCLUDED
