#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"


void crearListaS(tLista* lista)
{
    *lista = NULL;
}

int insertarOrdenadoRecur(tLista* lista, void* dato, int(*comparar)(const void*, const void*), unsigned cantBytes, int duplicado)
{
    int valor_comparacion = 1;
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue)
        return 0;

    if(*lista && (valor_comparacion = comparar(dato, (*lista)->info)) < 0)
    {
        return insertarOrdenadoRecur(&(*lista)->sig, dato, comparar, cantBytes, duplicado);
    }

    nue->info = malloc(cantBytes);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }

    if(valor_comparacion == 0 && !duplicado)
    {
        return 1;
    }

    memcpy(nue->info, dato, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = *lista;
    *lista = nue;

    return 1;
}


void R_recorrerLista(tLista* lista, void(*accion)(const void*))///Recursiva
{
    if(!*lista)
    {
        return;
    }
    accion((*lista)->info);
    R_recorrerLista(&(*lista)->sig, accion);
}



int buscarEnListaOrdenadaRecur(tLista* lista, void* dato, int(*comparar)(const void*, const void*))///Recursiva
{
    int cmp = 1;
    tNodo* elim;

    if(*lista && (cmp = comparar(dato, (*lista)->info)) > 0)
    {
        return buscarEnListaOrdenadaRecur(&(*lista)->sig, dato, comparar);
    }

    if(cmp)
        return 0;

    elim = *lista;
    memcpy(dato, elim->info, elim->tamInfo);
    *lista = elim->sig;
    free(elim->info);
    free(elim);
    return 1;
}
