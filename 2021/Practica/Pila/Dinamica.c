#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Dinamica.h"


void crearPila(tPila* pila)
{
    *pila = NULL;
}


int ponerEnPila(tPila* pila, const void* dato, unsigned cantBytes)
{
    tNodo* nNuevo = malloc(sizeof(tNodo));///se reserva memoria para todo el nodo/estructura
    if(!nNuevo)
    {
        return 0;
    }
    nNuevo->info = malloc(cantBytes); //info es un puntero
    if(!nNuevo->info)
    {
        free(nNuevo);
        return 1;
    }
    memcpy(nNuevo->info, dato, cantBytes);
    nNuevo->tamInfo = cantBytes;
    nNuevo->sig = *pila;
    *pila = nNuevo;
}

int pilaLlena(const tPila* pila, unsigned cantBytes)
{
    tNodo *aux = (tNodo*)malloc(sizeof(tNodo));
    if(!aux)
    {
        return 1;
    }
    aux->info = malloc(cantBytes);
    if(!aux->info)
    {
        free(aux);
        return 1;
    }

    free(aux->info);
    free(aux);
    return 0;
}

int verTope(const tPila *pila, void *dato, unsigned cantBytes)
{
    if(*pila == NULL)
    {
        return 0;
    }
    memcpy(dato, (*pila)->info, minimo(cantBytes, (*pila)->tamInfo));
    return 1;
}

int pilaVacia(const tPila *pila)
{
    return *pila == NULL;
}

void vaciarPila(tPila *pila)
{
    while(*pila)
    {
        tNodo *aux = *pila;

        *pila = aux->sig;
        free(aux->info);
        free(aux);
    }
}

int sacarDePila(tPila *pila, void *dato, unsigned cantBytes)
{
    tNodo *aux = *pila;
    if(aux == NULL)
    {
        return 0;
    }
    *pila = aux ->sig;
    memcpy(dato, aux->info, minimo(cantBytes, aux->tamInfo));
    free(aux->info);
    free(aux);
    return 1;
}




