#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDoble.h"


void creaLista(tLista* lista)
{
    *lista = NULL;
}

int listaVacia(const tLista* lista)
{
    return *lista == NULL;
}

int listaLlena(const tLista* lista, unsigned cantBytes)
{
    tNodo* aux =(tNodo*)malloc(sizeof(tNodo));
    if(!aux)
        return 1;
    aux->info = malloc(cantBytes);
    if(!aux->info)
        free(aux);
    return 1;

    free(aux->info);
    free(aux);
    return 0;
}

int vaciarLista(tLista* lista)
{
    tNodo* act;
    tNodo* elim;

    if(*lista)
    {
        act = *lista;
        while(act->ant)
            act = act->ant;

        while(act)
        {
            elim = act->sig;
            free(act->info);
            free(act);
            act = elim;
        }
        *lista = NULL;
    }
    return 1;
}


//void vaciarListaRecur(tLista* lista)///Recursiva
//{
//    tNodo* elim;
//
//    if(!*lista)
//        return;
//
//    if((*lista)->ant)
//    {
//        vaciarListaRecur(&(*lista)->ant);
//    }
//
//    if(*lista)
//    {
//        elim = (*lista)->sig;
//        free((*lista)->info);
//        free((*lista));
//        (*lista) = elim;
//        vaciarListaRecur(&(*lista));
//    }
//    *lista = NULL;
//}


int insertarAlInicio(tLista* lista, void* dato, unsigned cantBytes)
{
    tNodo* nue;
    tNodo* act = *lista;

    if(*lista)
    {
        act = *lista;
        while(act->ant)
            act = act->ant;
    }
    nue = (tNodo*)malloc(sizeof(tNodo));
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
    nue->sig = act;
    nue->ant = NULL;
    if(act)
        act->ant = nue;

    *lista = nue;
    return 1;
}

int insertarAlFinal(tLista* lista, void* dato, unsigned cantBytes)
{
    tNodo* nue;
    tNodo* act = *lista;

    if(*lista)
    {
        while(act->sig)
            act = act->sig;
    }

    nue = (tNodo*)malloc(sizeof(tNodo));
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
    nue->sig = NULL;
    nue->ant = act;
    if(act)
        act->sig = nue;

    *lista = nue;
    return 1;
}

int insertarEnListaOrdenado(tLista* lista, void* dato, unsigned cantBytes, int(*comparar)(const void*, const void*))
{
    tNodo* act = *lista;
    tNodo* nue;
    tNodo* auxSig;
    tNodo* auxAnt;
    int cmp;

    if(*lista)
    {
        while(act->sig && (comparar(act->info, dato)) > 0)
        {
            act = act->sig;
        }
        while(act->ant && (comparar(act->info, dato)) < 0)
        {
            act = act->ant;
        }

        cmp = comparar(act->info,dato);

        if(cmp == 0)
        {
            *lista = act;
            return 2;
        }
        else if(cmp > 0)
        {
            auxAnt = act;
            auxSig = act->sig;
        }
        else
        {
            auxAnt = act->ant;
            auxSig = act;
        }
    }
    else
    {
        auxAnt = NULL;
        auxSig = NULL;
    }

    nue = (tNodo*)malloc(sizeof(tNodo));
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
    nue->sig = auxSig;
    nue->ant = auxAnt;
    if(auxSig)
        auxSig->ant = nue;
    if(auxAnt)
        auxAnt->sig = nue;

    *lista = nue;

    return 1;
}


/////////////////////////////////////////////////////////////////////////////////////////
int insertarEnListaOrdenadoYacum(tLista* lista, void* dato, unsigned cantBytes, int(*compararCodigo)(const void*, const void*),int(*acum)(void**, unsigned*, const void*, unsigned))
{
    tNodo* act = *lista;
    tNodo* nue;
    tNodo* auxSig;
    tNodo* auxAnt;
    int cmp;

    if(act)
    {
        while(act->ant && (compararCodigo(act->info, dato)) > 0)
        {
            act = act->ant;
        }
        while(act->sig && (compararCodigo(act->info, dato)) < 0)
        {
            act = act->sig;
        }

        cmp = compararCodigo(act->info,dato);

        if(cmp == 0)
        {
            *lista = act;
            if(acum)
            {
                if(acum(&act->info, &act->tamInfo, dato, cantBytes) == 0)
                {
                    return 0;
                }
            }
            return 2;
        }
        else if(cmp < 0)
        {
            auxAnt = act;
            auxSig = act->sig;
        }
        else if(cmp > 0)
        {
            auxAnt = act->ant;
            auxSig = act;
        }
    }
    else
    {
        auxAnt = NULL;
        auxSig = NULL;
    }

    nue = (tNodo*)malloc(sizeof(tNodo));
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
    nue->sig = auxSig;
    nue->ant = auxAnt;
    if(auxSig)
        auxSig->ant = nue;
    if(auxAnt)
        auxAnt->sig = nue;

    *lista = nue;

    return 1;
}


/////////////////////////////////////////////////////////////////


int eliminarPorClave(tLista* lista, void* dato, unsigned cantBytes, int(*comparar)(const void*, const void*))
{
    tNodo* act;
    tNodo* auxSig;
    tNodo* auxAnt;
    int cmp;

    if(!*lista)
        return 0;

    act = *lista;
    while(act->sig && (comparar(act->info, dato)) > 0)
    {
        act = act->sig;
    }
    while(act->ant && (comparar(act->info, dato)) < 0)
    {
        act = act->ant;
    }

    cmp = comparar(act->info,dato);

    if(cmp != 0)///Sale por que NO encontro la clave
    {
        return 0;
    }
    auxAnt = act->ant;
    auxSig = act->sig;
    if(auxAnt)
    {
        auxAnt->sig = auxSig;
        *lista = auxAnt;
    }

    if(auxSig)
    {
        auxSig->ant = auxAnt;
        *lista = auxSig;
    }

    if(!auxAnt && !auxSig)
        *lista = NULL;

    memcpy(dato, act->info, MINIMO(cantBytes, act->tamInfo));

    free(act->info);
    free(act);
    return 1;
}

void recorrerListaIzq(tLista* lista, void(*accion)(const void*))
{
    while(*lista && (*lista)->ant)
    {
        lista = &(*lista)->ant;
    }
    while(*lista)
    {
        accion((*lista)->info);
        lista = &(*lista)->sig;
    }
}

void recorrerListaDer(tLista* lista, void(*accion)(const void*))
{
    while(*lista && (*lista)->sig)
    {
        lista = &(*lista)->sig;
    }
    while(*lista)
    {
        accion((*lista)->info);
        lista = &(*lista)->ant;
    }
}

void ordenarLista(tLista* lista, int(*comparar)(const void*, const void*))
{
    tLista *menor;
    tNodo *act;
    tNodo *auxAnt;
    tNodo *auxSig;

    if(*lista)
    {
        act = *lista;
        while(act->ant)
            act = act->ant;

        while(act->sig)
        {
            *lista = act;
            menor = buscarMenor(lista, comparar);
            if(*menor != *lista)
            {
                auxAnt = act->ant;
                auxSig = act;
                act = *menor;
                (*menor) = act->sig;
                act->sig = auxSig;
                act->ant = auxAnt;
                if(auxAnt)
                    auxAnt->sig = act;
                if(auxSig)
                    auxSig->ant = act;
            }
            act = act->sig;
        }
    }
}

tLista* buscarMenor(tLista* lista, int(*comparar)(const void*, const void*))
{
    tLista* menor = lista;
    lista = &(*lista)->sig;

    while(*lista)
    {
        if(comparar((*lista)->info, (*menor)->info) < 0)
        {
            menor = lista;
        }
        lista = &(*lista)->sig;
    }
    return menor;
}
