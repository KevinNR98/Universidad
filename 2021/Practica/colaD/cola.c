#include "cola.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void crearCola(tCola* cola)
{
    cola->pri = NULL;
    cola->ult = NULL;
}

int colaVacia(const tCola* cola)
{
    return cola->pri == NULL;
}

int colaLlena(const tCola* cola, unsigned cantBytes)
{
    tNodo* temp = malloc(sizeof(tNodo));
    if(temp == NULL)
    {
        return 1;
    }

    temp->info = malloc(cantBytes);

    if(temp->info == NULL)
    {
        free(temp);
        return 1;
    }
    free(temp->info);
    free(temp);
    return 0;
}

int ponerEnCola( tCola *cola, void* dato, unsigned cantBytes)
{
    tNodo* nue = (tNodo *)malloc(sizeof(tNodo));
    if(nue == NULL)
    {
        return 0;
    }
    nue->info = malloc(cantBytes);
    if(!(nue->info))
    {
        free(nue);
        return 0;
    }
    if(cola->ult == NULL)
    {
        cola->pri = nue;
    }
    else
    {
        cola->ult->sig = nue;
    }
    nue->sig = NULL;
    memcpy(nue->info, dato, cantBytes);
    nue->tamInfo = cantBytes;

    cola->ult = nue;

    return 1;
}

int sacarDeCola(tCola* cola, void* dato, unsigned cantBytes)
{
    tNodo* elim;
    if(cola->pri == NULL)
    {
        return 0;
    }
    elim = cola->pri;
    memcpy(dato, elim->info, minimo(cantBytes, elim->tamInfo));
    cola->pri = elim->sig;
    if(cola->pri == NULL)
    {
        cola->ult = NULL;
    }

    free(elim->info);
    free(elim);
    return 1;
}

void vaciarCola(tCola *cola)
{
    tNodo* elim;
    while(cola->pri)
    {
        elim = cola->pri;
        cola->pri = elim->sig;
        free(elim->info);
        free(elim);
    }
    cola->ult = NULL;//opcional
}

int verPrimero(const tCola *cola, void* dato, unsigned cantBytes)
{
    if(cola->pri == NULL)
    {
        return 0;
    }
    memcpy(dato, cola->pri->info, minimo(cantBytes, cola->pri->tamInfo));
    return 1;
}
