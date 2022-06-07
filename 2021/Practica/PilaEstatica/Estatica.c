#include "Estatica.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void crearPila(tPila *pila)
{
     pila->tope = TAM_PILA;
}


int pilaLlena(const tPila *pila, unsigned cantBytes)
{
    return (pila->tope < cantBytes + sizeof(unsigned));
}

int ponerEnPila(tPila *pila, const void *dato, unsigned cantBytes)
{
    if(pila->tope < cantBytes + sizeof(unsigned))
    {
        return 0;
    }
    pila->tope -=cantBytes;
    memcpy(pila->pila + pila->tope, dato, cantBytes);
    pila->tope -=sizeof(unsigned);
    memcpy(pila->pila + pila->tope, &cantBytes, sizeof(unsigned));
    return 1;
}

int verTope(const tPila *pila, void *dato, unsigned cantBytes)
{
    unsigned tamInfo;

    if(pila->tope == TAM_PILA)
    {
        return 0;
    }

    memcpy(&tamInfo, pila->pila + pila->tope, sizeof(unsigned));
    memcpy(dato,  pila->pila + pila->tope + sizeof(unsigned), minimo(cantBytes, tamInfo));
    return 1;
}

int pilaVacia(const tPila *pila)
{
    return pila->tope == TAM_PILA;
}

void vaciarPila(tPila *pila)
{
    pila->tope = TAM_PILA;
}


int sacarDePila(tPila *pila, void *dato, unsigned cantBytes)
{
    unsigned tamInfo;

    if(pila->tope == TAM_PILA)
    {
        return 0;
    }
    memcpy(&tamInfo, pila->pila + pila->tope, sizeof(unsigned));
    pila->tope += sizeof(unsigned);
    memcpy(dato, pila->pila + pila->tope, minimo(cantBytes, tamInfo));
    pila->tope += tamInfo;
    return 1;
}


