#define TDA_PILA_IMP_DINAMICA

#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "../TDAPila/TDAPila.h"

void crearPila(Pila* pp)
{
    *pp = NULL;
}



boolean apilar(Pila* pp, const void* elem, size_t tamElem)
{
    Nodo* nue = (Nodo*)malloc(sizeof(Nodo));
    void* elemNodo = malloc(tamElem);

    if(!nue || !elemNodo)
        return falso;

    memcpy(elemNodo, elem, tamElem);

    nue->elem = elemNodo;
    nue->tamElem = tamElem;


    nue->sig = *pp;
    *pp = nue;

    return verdadero;
}



boolean desapilar(Pila* pp, void * elem, size_t tamElem)
{
    Nodo* nae = *pp;

    if(!*pp)
        return falso;

    *pp = nae->sig;

    memcpy(elem, nae->elem, min(tamElem, nae->elem));


    free(nae->elem);
    free(nae);

    return verdadero;
}




boolean verTopePila(const Pila* pp, void * elem, size_t tamElem)
{
    if(!*pp)
        return falso;

    memcpy(elem, (*pp)->elem, min(tamElem, (*pp)->elem));

    return verdadero;
}



boolean pilaVacia(const Pila* pp)
{
    return !*pp;
}



boolean pilaLlena(const Pila* pp, size_t tamElem)
{
    Nodo* nue = malloc(sizeof(Nodo));
    void* elemNodo = malloc(tamElem);

    free(nue);
    free(elemNodo);

    return !nue || !elemNodo;
}


void vaciarPila(Pila* pp)
{
    Nodo* nae;
    while(*pp)
    {
        nae = *pp;
        *pp = nae->sig;
        free(nae->elem);
        free(nae);
    }
}

#include "../TDAPila/TDAPila.h"
