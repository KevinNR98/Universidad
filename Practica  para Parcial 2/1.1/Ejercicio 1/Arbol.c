#include <stdio.h>
#include <string.h>
#include "Arbol.h"

void crearArbol(tArbol* arbol)
{
    *arbol = NULL;
}

int insertarEnArbolRec(tArbol* arbol, void* dato, unsigned cantBytes, int(*cmpDni)(const void*, const void*))
{
    tNodoArbol* nue;
    int cmp;

    if(*arbol)
    {
        if((cmp = cmpDni((*arbol)->info, dato)) > 0)
        {
            return insertarEnArbolRec(&(*arbol)->izq, dato, cantBytes, cmpDni);
        }
        else if(cmp < 0)
        {
            return insertarEnArbolRec(&(*arbol)->der, dato, cantBytes, cmpDni);
        }
        else
        {
            return DUPLICADO;
        }
    }

    nue = (tNodoArbol*)malloc(sizeof(tNodoArbol));
    if(!nue)
        return 0;

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


void vacairArbol(tArbol* arbol)
{
    if(!*arbol)
        return;

    vacairArbol(&(*arbol)->izq);
    vacairArbol(&(*arbol)->der);
    free((*arbol)->info);
    free((*arbol));
    *arbol = NULL;
}

int buscarElemClaveArbol(const tArbol* arbol, void* dato, unsigned cantBytes, int(*cmpDni)(const void*, const void*))
{
    const tArbol* busq = NULL;

    if(!*arbol)
        return;

    if(cmpDni((*arbol)->info, dato) == 0)
    {
        busq = arbol;
    }
    else if((busq = buscarElemClaveArbol(&(*arbol)->izq, dato, )))
}
