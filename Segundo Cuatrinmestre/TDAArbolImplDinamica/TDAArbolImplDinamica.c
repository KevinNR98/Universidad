#include <stdio.h>

#define TDA_ARBOL_IMPL_DINAMICA
#include "../TDAArbol/TDAArbol.h"
#include "../Comun/Comun.h"

void crearArbol(Arbol *pa)
{
    *pa = NULL;
}

int insertarEnArbol(Arbol *pa, const void *elem, size_t tamElem, Cmp cmp)
{
    //Iterativa
    // int comp;

    // while (*pa && (comp = cmp(elem, (*pa)->elem) != 0))
    //     pa = comp < 0 ? &(*pa)->hIzq : pa = &(*pa)->hDer;

    // if (*pa)
    //     return DUPLICADO;

    // NodoA *nuevo = malloc(sizeof(NodoA));
    // void *elemNuevo = malloc(tamElem);

    // if (!nuevo || !elemNuevo)
    // {
    //     free(nuevo);
    //     free(elemNuevo);
    //     return SIN_MEMORIA;
    // }

    // memcpy(elemNuevo, elem, tamElem);
    // nuevo->elem = elemNuevo;
    // nuevo->tamElem = tamElem;
    // nuevo->hIzq = nuevo->hDer = NULL;

    // *pa = nuevo;

    // return TODO_OK;

    //Recursiva
    if (!*pa)
    {
        NodoA *nuevo = malloc(sizeof(NodoA));
        void *elemNuevo = malloc(tamElem);

        if (!nuevo || !elemNuevo)
        {
            free(nuevo);
            free(elemNuevo);
            return SIN_MEMORIA;
        }

         memcpy(elemNuevo, elem, tamElem);
         nuevo->elem = elemNuevo;
         nuevo->tamElem = tamElem;
        nuevo->hIzq = nuevo->hDer = NULL;

        *pa = nuevo;

        return TODO_OK;
    }

    int comp = cmp(elem, (*pa)->elem);

    if(comp == 0)
        return DUPLICADO;

    return  insertarEnArbol(comp < 0? &(*pa)->hIzq : &(*pa)->hDer, elem, tamElem, cmp);
}


boolean eliminarDeArbol(const Arbol* pa, void* elem, size_t tamElem, Cmp cmp)
{
    Arbol* pnae = buscarNodoEnArbol(pa, elem, cmp);

    if(!pnae)
        return falso;


    memcpy(elem, (*pnae)->elem, min(tamElem, (*pnae)->tamElem));

    eliminarNodoArbol(pnae);

    return verdadero;
}


Arbol* buscarNodoEnArbol(const Arbol* pa, void* elem, Cmp cmp)
{
    if(!*pa)
        return NULL;

    int comp = cmp(elem, (*pa)->elem);

    if(comp == 0)
        return 0;

    return buscarNodoEnArbol(comp < 0? &(*pa)->hIzq : &(*pa)->hDer, elem, cmp);
}


void eliminarNodoArbol(Arbol* pnae)
{
    if(!(*pnae)->hIzq && !(*pnae)->hDer)//Es una hoja
    {
        free((*pnae)->elem);
        free(*pnae);
        return;
    }   

    int hi = alturaArbol(&(*pnae)->hIzq);
    int hd = alturaArbol(&(*pnae)->hIzq);

    Arbol* pnreempl = hi > hd? mayorNodoArbol(&(*pnae)->hIzq) : menorNodo(&(*pnae)->hDer);

    (*pnae)->elem = (*pnreempl)->elem;
    
    eliminarNodoArbol(pnreempl);
}






boolean buscarEnArbol(const Arbol *pa, void *elem, size_t tamElem, Cmp cmp)
{
    // int comp;

    // while (*pa && (comp = cmp(elem, (*pa)->elem) != 0))
    //     pa = comp < 0 ? &(*pa)->hIzq : pa = &(*pa)->hDer;

    // if (!*pa) ///Si es null no lo encontro
    //     return falso;

    // memcpy(elem, (*pa)->elem, min(tamElem, (*pa)->tamElem));

    // return *pa != NULL;

    //Recursiva

    if(!*pa)
    return falso;

    int comp = cmp(elem, (*pa)->elem);

    if(comp == 0)
    {
        memcpy(elem,(*pa)->elem, min(tamElem, (*pa)->elem));
        return verdadero;
    }

    return buscarEnArbol(comp < 0? &(*pa)->hIzq : &(*pa)->hDer, elem, tamElem, cmp);
}

void recorrerArbolPreOrden(const Arbol *pa, Accion accion, void *datosAccion) //RID, funcion recursiva
{
    if (!*pa) //Caso Base
        return;

    accion((*pa)->elem, datosAccion);
    recorrerArbolEnOrden(&(*pa)->hIzq, accion, datosAccion);
    recorrerArbolEnOrden(&(*pa)->hDer, accion, datosAccion);
}

void recorrerArbolEnOrden(const Arbol *pa, Accion accion, void *datosAccion) //IRD, funcion recursiva
{
    if (!*pa) //Caso Base
        return;

    recorrerArbolEnOrden(&(*pa)->hIzq, accion, datosAccion);
    accion((*pa)->elem, datosAccion);
    recorrerArbolEnOrden(&(*pa)->hDer, accion, datosAccion);
}

void recorrerArbolPosOrden(const Arbol *pa, Accion accion, void *datosAccion) //IDR, funcion recursiva
{
    if (!*pa) //Caso Base
        return;

    recorrerArbolEnOrden(&(*pa)->hIzq, accion, datosAccion);
    recorrerArbolEnOrden(&(*pa)->hDer, accion, datosAccion);
    accion((*pa)->elem, datosAccion);
}

void vacairArbol(Arbol *pa)
{
    if (!*pa)
        return;

    vacairArbol(&(*pa)->hIzq);
    vacairArbol(&(*pa)->hDer);
    free((*pa)->elem);
    free(*pa);
    *pa = NULL;
}

int alturaArbol(const Arbol* pa)
{
    if(!*pa)
        return 0;

    int altIzq = alturaArbol(&(*pa)->hIzq);
    int altDer = alturaArbol(&(*pa)->hDer);

    return max(altIzq, altDer) + 1;
}

int contarElemntosArbol(const Arbol* pa)
{
    if(!*pa)
        return 0;

    return contarElemntosArbol(&(*pa)->hIzq) + contarElemntosArbol(&(*pa)->hDer) + 1;
}

int contarHojasArbol(const Arbol* pa);


