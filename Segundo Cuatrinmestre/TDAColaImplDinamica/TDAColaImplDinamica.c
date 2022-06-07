#include <stdlib.h>
#include <string.h>

#define TDA_COLA_IMPL_DINAMICA
#include "../TDACola/TDACola.h"


void crearCola(Cola* pc)
{
    pc->frente = pc->fondo = NULL;

}


boolean encolar(Cola* pc, const void* elem, size_t tamElem)
{
    Nodo* nue =(Nodo*)malloc(sizeof(Nodo));
    void* elemNodo = malloc(tamElem);

    if(!nue || !elemNodo)
    {
        free(nue);
        free(elemNodo);
        return falso;
    }

    memcpy(elemNodo, elem, tamElem);

    nue->elem = elemNodo;
    nue->tamElem = tamElem;

    if(!pc->frente)
        pc->frente = nue;//3
    else
        pc->fondo->sig = nue;//1

    pc->fondo = nue;//2


    return verdadero;

}


boolean desencolar(Cola* pc, void* elem, size_t tamElem)
{
    Nodo* nae = pc->frente;//1

    if(!pc->frente)
        return falso;

    pc->frente = nae->sig;//2

    if(!pc->frente)
        pc->fondo = NULL;//3

    memcpy(elem, nae->elem, min(tamElem, nae->tamElem));

    free(nae->elem);
    free(nae);

    return verdadero;
}


boolean verFrenteDeCola(const Cola* pc, void* elem, size_t tamElem)
{
    Nodo* frente = pc->frente;

    if(!pc->frente)
        return falso;

    memcpy(elem, frente->elem, min(tamElem, frente->tamElem));

    return verdadero;
}


boolean colaVacia(const Cola* pc)
{
    return !pc->frente;
}


boolean colaLlena(const Cola*  pc, size_t tamElem)
{
    void* nue = malloc(sizeof(Nodo));
    void* elemNodo = malloc(tamElem);

    free(nue);
    free(elemNodo);

    return verdadero;

}
void vaciarCola(Cola* pc)
{
    Nodo* nae;

    while(pc->frente)
    {
        nae = pc->frente;//1
        pc->frente = nae->sig;//2

        free(nae->elem);
        free(nae);
    }

    pc->fondo = NULL;//3
}
