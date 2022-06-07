#include <memory.h>

#define TDA_PILA_IMPL_ESTATICA

#include "../TDAPila/TDAPila.h"



void crearPila(Pila* pp)
{
    pp->tope = 0;
}


boolean apilar(Pila* pp, const void* elem, size_t tamElem)
{
    if(tamElem + sizeof(size_t) > TAM_PILA - pp->tope)/// hago esto y no llamo a la funcion para ser mas eficiente y no tener que llamar a otra primitiva desde una primitiva
        return falso;

    memcpy(pp->vPila + pp->tope, elem, tamElem);
    pp->tope += tamElem;
    *(size_t*)(pp->vPila + pp->tope) = tamElem; /// memcpy ((pp->vPila + pp->tope), &tamElem, sizeof(size_t));
    pp->tope += sizeof(size_t);

    return verdadero;
}


boolean desapilar(Pila* pp, void * elem, size_t tamElem)
{
    if(pp->tope == 0)
        return falso;

    pp->tope -= sizeof(size_t);
    size_t tamElemApilado = *(size_t*)(pp->vPila + pp->tope);
    pp->tope -= tamElemApilado;
    memcpy(elem, pp->vPila + pp->tope, min(tamElem, tamElemApilado));

    return verdadero;
}



boolean verTopePila(const Pila* pp, void * elem, size_t tamElem)
{
    unsigned tope = pp->tope;

    if(pp->tope == 0)
        return falso;

    tope -= sizeof(size_t);
    size_t tamElemApilado = *(size_t*)(pp->vPila + tope);
    tope -= tamElemApilado;
    memcpy(elem, pp->vPila + tope, min(tamElem, tamElemApilado));

    return verdadero;

}



boolean pilaVacia(const Pila* pp)
{
    return pp->tope == 0;
}



boolean pilaLlena(const Pila* pp, size_t tamElem)
{
    size_t espacioLibre = TAM_PILA - pp->tope;

    return tamElem + sizeof(size_t) > espacioLibre;
}



void vaciarPila(Pila* pp)
{
    pp->tope = 0;
}
