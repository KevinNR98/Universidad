#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "arbol.h"

void crearArbol(tArbol* arbol)
{
    *arbol = NULL;
}


int insertarEnArbolRec(tArbol* arbol, void* dato, unsigned cantBytes, int(*compararDNI)(const void*, const void*))
{
    tNodoArbol* nue;
    int cmp;

    if(*arbol)
    {
        if((cmp = compararDNI((*arbol)->info, dato)) > 0)
        {
            return insertarEnArbolRec(&(*arbol)->izq, dato, cantBytes, compararDNI);
        }
        else if(cmp < 0)
        {
            return insertarEnArbolRec(&(*arbol)->der, dato, cantBytes, compararDNI);
        }
        else
        {
            return DUPLICADO;
        }
    }


    nue = (tNodoArbol*)malloc(sizeof(tNodoArbol));
    if(!nue)
    {
        return 0;
    }

    nue->info = malloc(cantBytes);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, dato, cantBytes);
    nue->tamInfo = cantBytes;
    nue->izq = NULL;
    nue->der = NULL;
    *arbol = nue;

    return 1;
}


void vaciarArbol(tArbol* arbol)
{
    if(!*arbol)
        return;

    vaciarArbol(&(*arbol)->izq);
    vaciarArbol(&(*arbol)->der);
    free((*arbol)->info);
    free((*arbol));
    *arbol = NULL;
}
