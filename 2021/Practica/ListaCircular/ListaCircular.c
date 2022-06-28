#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaCircular.h"


void crearLista(tLista* lista)
{
    *lista = NULL;
}

int insertarAlPrincipio(tLista* lista, void* dato, unsigned cantBytes)
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
    if(*lista == NULL)
    {
        nue->sig = nue;

    }
    else
    {
        nue->sig = (*lista)->sig;
        (*lista)->sig = nue;

    }
    *lista = nue;

    return 1;
}

int insertarAlFinal(tLista* lista, void* dato, unsigned cantBytes)
{
    tNodo* act;
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue)
        return 0;

    if(*lista)
    {
        act = *lista;
        while((*lista)->sig != act)
        {
            lista = &(*lista)->sig;
        }
    }

    nue->info = malloc(cantBytes);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, dato, cantBytes);
    nue->tamInfo = cantBytes;
    if(*lista == NULL)
    {
        nue->sig = nue;
        *lista = nue;

    }
    else
    {
        nue->sig = (*lista)->sig;
        (*lista)->sig = nue;
    }

    return 1;
}

void recorrerLista(tLista* lista, void(*accion)(const void*))
{
    void* iniList = *lista;

    if(*lista)
    {
        do
        {
            accion((*lista)->info);
            lista = &(*lista)->sig;
        }
        while(iniList != *lista);
    }
}

