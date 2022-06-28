#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PilaCircular.h"

void crearPila(tPila* pila)
{
    *pila = NULL;
}


int ponerEnPila(tPila* pila, void* dato, unsigned cantBytes)
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

    if(*pila == NULL)
    {
        nue->sig = nue;
        *pila = nue;
    }
    else
    {
        nue->sig = (*pila)->sig;
        (*pila)->sig = nue;
    }
    return 1;
}

int sacarDePila(tPila* pila, void* dato, unsigned cantBytes)
{
    tNodo* elim;

    if(*pila == NULL)
        return 0;

    elim = (*pila)->sig;
    memcpy(dato, elim->info, MINIMO(cantBytes, elim->tamInfo));
    if(elim == *pila)
    {
        *pila = NULL;
    }
    else
    {
        (*pila)->sig = elim->sig;
    }
    free(elim->info);
    free(elim);
    return 1;
}

int verTope(const tPila* pila, void* dato, unsigned cantBytes)
{
    if(*pila == NULL)
        return 0;
    memcpy(dato, (*pila)->sig->info, MINIMO(cantBytes, (*pila)->sig->info));
    return 1;
}


void vaciarPila(tPila* pila)
{
    tNodo* elim = *pila;

    while(*pila)
    {
        if(elim == *pila)
            *pila = NULL;
        else
            (*pila)->sig = elim->sig;

        free(elim->sig);
        free(elim);
    }
}

int pilaVacia(const tPila* pila)
{
    return *pila == NULL;
}


