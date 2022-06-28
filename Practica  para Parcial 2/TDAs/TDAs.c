#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "TDAs.h"



///////////////////////////////////ARBOL BINARIO//////////////////////////////////////////
void crearArbol(Arbol* pa)
{
    *pa = NULL;
}


int insertarEnArbol(Arbol* pa, void* elem, size_t tamElem, Cmp cmp)
{
    if(!*pa)
    {
        NodoA* nue = malloc(sizeof(NodoA));
        void* elemNuevo = malloc(tamElem);

        if(!nue || !elemNuevo)
        {
            free(nue);
            free(elemNuevo);
            return SIN_MEMORIA;
        }

        memcpy(elemNuevo, elem, tamElem);
        nue->elem = elemNuevo;
        nue->tamElem = tamElem;
        nue->hIzq = nue->hDer = NULL;

        *pa = nue;

        return TODO_OK;
    }

    int comp = cmp(elem, (*pa)->elem);

    if(comp == 0)
        return DUPLICADO;

    return insertarEnArbol(comp < 0? &(*pa)->hIzq : &(*pa)->hDer, elem, tamElem, cmp);
}



int buscarEnArbol(const Arbol* pa, void* elem, size_t tamElem, Cmp cmp)
{
    if(!*pa)
        return FALSO;

    int comp = cmp(elem, (*pa)->elem);

    if(comp == 0)
    {
        memcpy(elem, (*pa)->elem, min((*pa)->tamElem, tamElem));
        return TODO_OK;
    }

    return buscarEnArbol(comp < 0? &(*pa)->hIzq : &(*pa)->hDer, elem, tamElem, cmp);
}






///////////////////////////////LISTA DOBLE ENLAZADA/////////////////////////////////////////////

void crearListaD(ListaD* pl)
{
    *pl = NULL;
}

int insertarEnListaOrd(ListaD* pl, void* elem, size_t tamElem, Cmp cmp)
{
    NodoD* act = *pl, *ant, *sig;

    if(!pl)
    {
        ant = sig = NULL;
    }
    else
    {
        while(act->ant && cmp(elem, act->elem) < 0)
            act = act->ant;
        while(act->sig && cmp(elem, act->elem) > 0)
            act = act->sig;

        int comp = cmp(elem, act->elem);

        if(comp == 0)
            return DUPLICADO;

        if(comp < 0)
        {
            sig = act;
            ant = act->sig;
        }
        else
        {
            act = ant;
            sig = act->sig;
        }
    }


    NodoD* nue = malloc(sizeof(NodoD));
    void* elemNue = malloc(tamElem);

    if(!nue || !elemNue)
    {
        free(nue);
        free(elemNue);
        return SIN_MEMORIA;
    }

    memcpy(elemNue, elem, tamElem);
    nue->elem = elemNue;
    nue->tamElem = tamElem;

    nue->ant = ant;
    nue->sig sig;

    if(ant)
        ant->sig = nue;
    if(sig)
        sig->ant = nue;

    *pl = nue;

    return TODO_OK;
}

//////////////////////////////////////////////////////////////////////////
