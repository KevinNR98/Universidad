#include <stdio.h>
#include <stdlib.h>
#include "tda.h"
#include <memory.h>

///////PILA DINAMICA///////////////////
void crearPila(Pila* pila)
{
    *pila = NULL;
}


int apilar(Pila* pila, const void* elem, size_t tamElem)
{
    Nodo* nue = malloc(sizeof(Nodo));
    void* elemNodo = malloc(tamElem);

    if(!nue || !elemNodo)
    {
        free(nue);
        free(elemNodo);
        return ERROR;
    }

    memcpy(elemNodo, elem, tamElem);

    nue->elem = elemNodo;
    nue->tamElem = tamElem;

    nue->sig = *pila;
    *pila = nue;

    return TODO_OK;
}


int desapilar(Pila* pila, void* elem, size_t tamElem)
{
    Nodo* nae = *pila;

    if(!*pila)
        return ERROR;

    memcpy(elem, nae->elem, min(tamElem, nae->tamElem));

    *pila = nae->sig;

    free(nae->elem);
    free(nae);

    return TODO_OK;
}


int verTopePila( Pila* pila, void* elem, size_t tamElem)
{
    if(!*pila)
        return ERROR;

    memcpy(elem, (*pila)->elem, min(tamElem, (*pila)->tamElem));

    return TODO_OK;
}



int pilaLlena(Pila* pila, size_t tamElem)
{
    Nodo* nue = malloc(sizeof(Nodo));
    void* elemNodo = malloc(tamElem);

    free(elemNodo);
    free(nue);

    return !nue || !elemNodo;
}


int pilaVacia(Pila* pila)
{
    return *pila == NULL;
}
void vaciarPila(Pila* pila)
{
    Nodo* nae;

    while(!*pila)
    {
        nae = *pila;
        *pila = nae->sig;
        free(nae->elem);
        free(nae);
    }
}
////////////////////////////////////////////////////////////////////////
////////////////PILA ESTATICA//////////////////////////////////////////
void crearPilaEs(PilaEs* pila)
{
    pila->tope = 0;
}

int apilarEs(PilaEs* pila, const void* elem, size_t tamElem)
{
    if(tamElem + sizeof(size_t) > TAM_PILA - pila->tope)
        return SIN_MEMORIA;

    memcpy(pila->vPila + pila->tope, elem, tamElem);
    pila->tope += tamElem;
    *(size_t*)(pila->vPila + pila->tope) = tamElem;
    pila->tope = sizeof(size_t);

    return TODO_OK;
}


int desapilarEs(PilaEs* pila, void* elem, size_t tamElem)
{
    if(pila->tope == 0)
        return ERROR;

    pila->tope -= sizeof(size_t);
    size_t tamApilado = *(size_t*)(pila->vPila + pila->tope);
    pila->tope -= tamApilado;
    memcpy(elem, pila->vPila + pila->tope, min(tamApilado, tamElem));

    return TODO_OK;
}



int verTopePilaEs(PilaEs* pila, void* elem, size_t tamElem)
{
    size_t tope = pila->tope;

    if(pila->tope == 0)
        return ERROR;


    tope -= sizeof(size_t);
    size_t tamApilado = *(size_t*)(pila->vPila + tope);
    tope -= tamApilado;
    memcpy(elem, pila->vPila + tope, min(tamElem, tamApilado));

    return TODO_OK;
}



int pilaLlenaEs(PilaEs* pila, size_t tamElem)
{
    size_t espacioLibre = TAM_PILA - pila->tope;

    return tamElem + sizeof(size_t) > espacioLibre;
}

int pilaVaciaEs(PilaEs* pila)
{
    return pila->tope == 0;
}


void vaciarPilaEs(PilaEs* pila)
{
    pila->tope = 0;
}



///////////////////COLA DINAMICA//////////////////////

void crearCola(Cola* cola)
{
    cola->frente = cola->fondo = NULL;
}

int encolar(Cola* cola, const void* elem, size_t tamElem)
{
    Nodo* nue = malloc(sizeof(Nodo));
    void* elemNodo = malloc(tamElem);

    if(!nue || !elemNodo)
    {
        free(nue);
        free(elemNodo);
        return ERROR;
    }

    memcpy(elemNodo, elem, tamElem);
    nue->elem = elemNodo;
    nue->tamElem = tamElem;

    if(!cola->frente)
        cola->frente = nue;
    else
        cola->fondo->sig = nue;

    cola->fondo = nue;

    return TODO_OK;
}

int desencolar(Cola* cola, void* elem, size_t tamElem)
{
    Nodo* nae = cola->frente;

    if(!cola->frente)
        return ERROR;

    cola->frente = nae->sig;

    if(!cola->frente)
        cola->fondo = NULL;

    memcpy(elem, nae->elem, min(tamElem, nae->tamElem));

    free(nae->elem);
    free(nae);
    return TODO_OK;
}

int verFrenteCola(Cola* cola, void* elem, size_t tamElem)
{
    Nodo* frente = cola->frente;

    if(!cola->frente)
        return ERROR;

    memcpy(elem, frente->elem, min(tamElem, frente->tamElem));

    return TODO_OK;
}

int colaLlena(const Cola* cola, size_t tamElem)
{
    Nodo* nue = malloc(sizeof(Nodo));
    void* elemNodo = malloc(tamElem);

    free(nue);
    free(elemNodo);

    return !nue || !elemNodo;

}
int colaVacia(const Cola* cola)
{
    return !cola->frente;
}
void vaciarCola(Cola* cola)
{
    Nodo* nae;

    while(!cola->frente)
    {
        nae = cola->frente;
        cola->frente = nae->sig;

        free(nae->elem);
        free(nae);
    }
    cola->fondo = NULL;
}


///////////COLA ESTATICA/////////////////////////

void crearColaEs(ColaEs* cola)
{
    cola->fondo = cola->frente = 0;
    cola->tamDisponible = TAM_COLA;
}

int encolarEs(ColaEs* cola, const void* elem, size_t tamElem)
{
    if(tamElem + sizeof(size_t) > cola->tamDisponible)
        return SIN_MEMORIA;

    cola->fondo = copiarAVector(cola->vCola, cola->vCola + TAM_COLA - 1, cola->fondo, &tamElem, sizeof(size_t));
    cola->fondo = copiarAVector(cola->vCola, cola->vCola + TAM_COLA - 1, cola->fondo, elem, tamElem);

    cola->tamDisponible += tamElem + sizeof(size_t);

    return TODO_OK;
}

char* copiarAVector(char* vecLIzq, char* vecLDer, char* iniCopia, void* elem, size_t tamElem)
{
    size_t tamACopiar = tamElem;
    size_t cantPrimeraCopia = min(tamACopiar, vecLIzq - iniCopia);
    memcpy(iniCopia, elem, cantPrimeraCopia);
    tamACopiar -= cantPrimeraCopia;

    if(tamACopiar > 0)
    {
        memcpy(vecLIzq, elem + cantPrimeraCopia, tamACopiar);
        return vecLIzq + tamACopiar;
    }
    else
        return iniCopia + tamElem;
}

int desencolarEs(ColaEs* cola, void* elem, size_t tamElem)
{
    size_t tamElemEncolado;

    if(cola->tamDisponible == TAM_COLA)
        return ERROR;

    cola->frente = copiarDeVector(cola->vCola, cola->vCola + TAM_COLA, cola->frente, &tamElemEncolado, sizeof(size_t), sizeof(size_t));
    cola->frente = copiarDeVector(cola->vCola, cola->vCola + TAM_COLA, cola->frente, elem, tamElem, tamElemEncolado);

    cola->tamDisponible += tamElem + sizeof(size_t);

    return TODO_OK;
}

char* copiarDeVector(char* vecLIzq, char* vecLDer, char* iniCopia, void* elem, size_t tamElem, size_t tamElemEncolado)
{
    size_t tamACopiar = min(tamElem, tamElemEncolado);
    size_t cantPrimeraCopia = min(tamACopiar, vecLIzq - iniCopia);
    memcpy(elem, iniCopia, cantPrimeraCopia);
    tamACopiar -= cantPrimeraCopia;

    if(tamACopiar > 0)
    {
        memcpy(elem + cantPrimeraCopia, vecLIzq, tamACopiar);
        return (char*)vecLIzq + tamElemEncolado - cantPrimeraCopia;
    }
    else
        return iniCopia + tamElemEncolado;

}

int verFondoColoEs(ColaEs* cola, const void* elem, size_t tamElem)
{
    size_t tamElemEncolado;
    char* frente = cola->frente;

    if(cola->tamDisponible == TAM_COLA)
        return ERROR;

    frente = copiarDeVector(cola->vCola, cola->vCola + TAM_COLA, cola->frente, &tamElemEncolado, sizeof(size_t), sizeof(size_t));
    copiarDeVector(cola->vCola, cola->vCola + TAM_COLA, cola->frente, elem, tamElem, tamElemEncolado);

    return TODO_OK;
}


int colaLlenaEs(const ColaEs* cola, size_t tamElem)
{
    return cola->tamDisponible < tamElem + sizeof(size_t);
}
int colaVaciaEs(const ColaEs* cola)
{
    return cola->tamDisponible == TAM_COLA;
}
void vaciarColaEs(ColaEs* cola)
{
    cola->frente = cola->fondo = cola->vCola;
    cola->tamDisponible = TAM_COLA;
}




////////////////LISTA SIMPLEMENTE ENLAZADA DINAMICA//////////
void crearLista(Lista* lista)
{
    *lista = NULL;
}

int insertarEnListaOrd(Lista* lista, const void* elem, size_t tamElem, Cmp cmp)
{
    Nodo* nue;
    void* elemNodo;

    while(*lista && cmp(elem, (*lista)->elem) > 0)
        lista = &(*lista)->sig;

    if(*lista && cmp(elem, (*lista)->elem) == 0)
        return DUPLICADO;

    nue = malloc(sizeof(Nodo));
    elemNodo = malloc(tamElem);

    if(!nue || !elemNodo)
    {
        free(nue);
        free(elemNodo);
        return SIN_MEMORIA;
    }

    nue->elem = elemNodo;
    memcpy(elemNodo, elem, tamElem);
    nue->tamElem = tamElem;

    nue->sig = *lista;
    *lista = nue;

    return TODO_OK;
}

int sacarDeListaOrd(Lista* lista, void* elem, size_t tamElem, Cmp cmp)
{
    Nodo* nae;

    while(*lista && cmp(elem, (*lista)->elem) > 0)
        lista = &(*lista)->sig;

    if(*lista && cmp(elem, (*lista)->elem) < 0)
        return ERROR;

    nae = *lista;
    *lista = nae->sig;

    memcpy(elem, nae->elem, min(tamElem, nae->tamElem));

    free(nae->elem);
    free(nae);

    return TODO_OK;
}


int buscarEnListaOrd(Lista* lista, void* elem, size_t tamElem, Cmp cmp)
{
    Nodo* nab = *lista;

    while(*lista && cmp(elem, (*lista)->elem) > 0)
        lista = &(*lista)->sig;

    if(*lista && cmp(elem, (*lista)->elem) == 0)
        return DUPLICADO;

    memcpy(elem, nab->elem, min(tamElem, nab->tamElem));

    return TODO_OK;
}



int ordenarLista(Lista* lista, Cmp cmp)
{
    Lista lOrd = NULL;
    Lista* plOrd;
    Nodo* nodo;

    while(*lista)
    {
        nodo = *lista;
        *lista = nodo->sig;

        plOrd = &lOrd;

        while(*plOrd && cmp(nodo->elem, (*plOrd)->elem) > 0)
            plOrd = &(*plOrd)->sig;

        nodo->sig = *plOrd;
        *plOrd = nodo;
    }
    *lista = lOrd;

    return TODO_OK;
}
int listaVacia(Lista* lista)
{
    return *lista == NULL;
}


int listaLlena(Lista* lista, size_t tamElem)
{
    Nodo* nue = malloc(sizeof(Nodo));
    void* elemNodo = malloc(tamElem);

    free(nue);
    free(elemNodo);

    return !nue || !elemNodo;
}


void vaciarLista(Lista* lista)
{
    Nodo* nae;

    while(*lista)
    {
        nae = *lista;
        *lista = nae->sig;
        free(nae->elem);
        free(nae);
    }
}


//////////////////////////////////////////////////////

//void crearPila(Pila* pp)
//{
//    *pp = NULL;
//}
//
//
//int apilar(Pila* pp, const void* elem, size_t tamElem)
//{
//    Nodo* nue = malloc(sizeof(Nodo));
//    void* elemNodo = malloc(tamElem);
//
//    if(!nue || !elemNodo)
//    {
//        free(nue);
//        free(elemNodo);
//        return ERROR;
//    }
//
//    memcpy(elemNodo, elem, tamElem);
//    nue->elem = elemNodo;
//    nue->tamElem = tamElem;
//
//    nue->sig = *pp;
//    *pp = nue;
//
//    return TODO_OK;
//}
//
//int desapilar(Pila* pp, void* elem, size_t tamElem)
//{
//    Nodo* nae = *pp;
//
//    if(!*pp)
//        return ERROR;
//
//    memcpy(elem, nae->elem, min(tamElem, nae->tamElem));
//
//    *pp = nae->sig;
//
//    free(nae->elem);
//    free(nae);
//
//    return TODO_OK;
//}
//
//int verTopePila(Pila* pp, void* elem, size_t tamElem)
//{
//    Nodo* nav = malloc(sizeof(Nodo));
//    if(!*pp)
//        return ERROR;
//
//    nav = *pp;
//    memcpy(elem, nav->elem, min(tamElem, nav->tamElem));
//    return TODO_OK;
//}
//
//int pilaVacia(Pila* pp)
//{
//    return !*pp;
//}
//
//int pilaLlena(Pila* pp, size_t tamElem)
//{
//    Nodo* nue = malloc(sizeof(Nodo));
//    void* elemNodo = malloc(tamElem);
//
//
//    free(elemNodo);
//    free(nue);
//
//    return !nue || !elemNodo;
//}
//
//void vaciarPila(Pila* pp)
//{
//    Nodo* nae;
//
//    while(*pp)
//    {
//        nae = *pp;
//        *pp = nae->sig;
//
//        free(nae->elem);
//        free(nae);
//    }
//}
//
//////////////////////////////////////////////////////////////////
//
//void crearCola(Cola* pc)
//{
//    pc->frente = pc->fondo = NULL;
//}
//
//int encolar(Cola* pc, const void* elem, size_t tamElem)
//{
//    Nodo* nue = malloc(sizeof(Nodo));
//    void* elemNodo = malloc(tamElem);
//
//    if(!nue || !elemNodo)
//    {
//        free(nue);
//        free(elemNodo);
//        return ERROR;
//    }
//
//    memcpy(elemNodo, elem, tamElem);
//    nue->elem = elemNodo;
//    nue->tamElem = tamElem;
//
//    if(!pc->frente)
//        pc->frente = nue;
//    else
//        pc->fondo->sig = nue;
//
//    pc->fondo = nue;
//
//    return TODO_OK;
//}
//
//int desencolar(Cola* pc, void* elem, size_t tamElem)
//{
//    Nodo* nae = pc->frente;
//
//    if(!pc->frente)
//        return ERROR;
//
//    pc->frente = nae->sig;
//
//    if(!pc->frente)
//        pc->fondo = NULL;
//
//    memcpy(elem, nae->elem, min(tamElem, nae->tamElem));
//
//    free(nae->elem);
//    free(nae);
//
//    return TODO_OK;
//}
//
//int colaVacia(const Cola* pc)
//{
//    return !pc->frente;
//}
//
//int colaLlena(const Cola* pc, size_t tamElem)
//{
//    Nodo* nue = malloc(sizeof(Nodo));
//    void* elemNodo = malloc(tamElem);
//
//    free(nue);
//    free(elemNodo);
//
//    return !nue || !elemNodo;
//}
//
//int verFrenteCola(Cola* pc, void* elem, size_t tamElem)
//{
//    Nodo* frente = pc->frente;
//
//    if(!pc->frente)
//        return ERROR;
//
//    memcpy(elem, frente->elem, min(tamElem, frente->tamElem));
//
//    return TODO_OK;
//}
//
//int verFondoColo(Cola* pc, const void* elem, size_t tamElem)
//{
//    Nodo* fondo = pc->fondo;
//
//    if(!pc->fondo)
//        return ERROR;
//
//    memcpy(elem, fondo->elem, min(tamElem, fondo->tamElem));
//
//    return TODO_OK;
//}
//
//
//void vaciarCola(Cola* pc)
//{
//    Nodo* nae;
//
//    while(pc->frente)
//    {
//        nae = pc->frente;
//        pc->frente =nae->sig;
//
//        free(nae->elem);
//        free(nae);
//    }
//    pc->fondo = NULL;
//}
//
//
/////////////////////////////////////////////////////////////////
//
//void crearLista(Lista* pl)
//{
//    *pl = NULL;
//}
//
//
//int insertarEnListaOrd(Lista* pl, const void* elem, size_t tamElem, Cmp cmp)
//{
//    Nodo* nue;
//    void* elemNodo;
//
//    while(*pl && cmp(elem,(*pl)->elem) > 0)
//        pl = &(*pl)->sig;
//
//    if(*pl && cmp(elem,(*pl)->elem) == 0)
//        return DUPLICADO;
//
//    nue = malloc(sizeof(Nodo));
//    elemNodo = malloc(tamElem);
//
//    if(!nue || !elemNodo)
//    {
//        free(nue);
//        free(elemNodo);
//        return ERROR;
//    }
//
//    memcpy(elemNodo, elem, tamElem);
//    nue->elem = elemNodo;
//    nue->tamElem = tamElem;
//
//    nue->sig = *pl;
//    *pl = nue;
//
//    return TODO_OK;
//}
//
//
//int sacarDeListaOrd(Lista* pl, void* elem, size_t tamElem, Cmp cmp)
//{
//    Nodo* nae = *pl;
//
//    while(*pl && cmp(elem,(*pl)->elem) > 0)
//        pl = &(*pl)->sig;
//
//    if(*pl && cmp(elem,(*pl)->elem) < 0)
//        return ERROR;
//
//    memcpy(elem, nae->elem, min(tamElem, nae->tamElem));
//
//    *pl = nae->sig;
//
//    free(nae->elem);
//    free(nae);
//    return TODO_OK;
//}
//
//
//int buscarEnListaOrd(Lista* pl, void* elem, size_t tamElem, Cmp cmp)
//{
//    Nodo* nab = *pl;
//
//    while(nab && cmp(elem, nab->elem) > 0)
//        nab = &(nab)->sig;
//
//    if(nab && cmp(elem, nab->elem) == 0)
//        return ERROR;
//
//    memcpy(elem, nab->elem, min(tamElem, nab->tamElem));
//}
