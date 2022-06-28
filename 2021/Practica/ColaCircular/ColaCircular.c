#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ColaCircular.h"

void crearCola(tCola* cola)
{
    *cola = NULL;
}

int ponerEnCola(tCola* cola, void* dato, unsigned cantBytes)
{
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
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
    if(*cola == NULL)
    {
        nue->sig = nue;
    }
    else
    {
        nue->sig = (*cola)->sig;
        (*cola)->sig = nue;
    }
    *cola = nue;
    return 1;
}


int sacarDeCola(tCola* cola, void* dato, unsigned cantBytes)
{
    tNodo* elim;

    if(*cola == NULL)
        return 0;

    elim = (*cola)->sig;
    memcpy(dato, elim->info, MINIMO(cantBytes, elim->tamInfo));
    if(elim == *cola)
        *cola = NULL;
    else
        (*cola)->sig = elim->sig;

    free(elim->sig);
    free(elim);
    return 1;
}

int colaVacia(const tCola* cola)
{
    return *cola == NULL;
}

void vaciarCola(tCola* cola)
{
    tNodo* elim;

    while(*cola)
    {
        if(*cola == NULL)
        {
            *cola = NULL;
        }
        else
        {
            (*cola)->sig = elim->sig;
        }
    }
    free(elim->sig);
    free(elim);
}

