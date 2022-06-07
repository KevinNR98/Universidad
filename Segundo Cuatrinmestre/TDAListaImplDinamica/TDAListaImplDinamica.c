#include <string.h>

#define TDA_LISTA_IMPL_DINAMICA
#include "../TDALista/TDALista.h"


void crearLista(Lista* pl)
{
    *pl = NULL;
}



int insertarEnListaOrd(Lista* pl, void* elem, size_t tamElem, Cmp cmp)
{
    Nodo* nue;
    void* elemNodo;

    while(*pl && cmp(elem, (*pl)->elem) > 0)///si esta vacia o ins al prin o fin
        pl = &(*pl)->sig;

    if(*pl && cmp(elem, (*pl)->elem) == 0)///para ver si el elemento que voy insertar ya esta en la lista
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

    nue->sig = *pl;
    *pl = nue;

    return TODO_OK;
}



int insertarActualizarEnListaOrd(Lista* pl, void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar)
{
    Nodo* nue;
    void* elemNodo;

    while(*pl && cmp(elem, (*pl)->elem) > 0)///si esta vacia o ins al prin o fin
        pl = &(*pl)->sig;

    if(*pl && cmp(elem, (*pl)->elem == 0))///para ver si el elemento que voy insertar ya esta en la lista
     {
         actualizar((*pl)->elem, elem);
        return DUPLICADO;
     }   
    
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

    nue->sig = *pl;
    *pl = nue;

    return TODO_OK;


}


boolean eliminarDeListaOrd(Lista* pl, void* elem, size_t tamElem, Cmp cmp)
{
    Nodo* nae;

    while(*pl && cmp(elem, (*pl)->elem) > 0)
        pl = &(*pl)->sig;

    if(!*pl || cmp(elem, (*pl)->elem) < 0)///si no encotro el elem a eliminar
        return falso;

    nae = *pl;//1
    *pl = nae->sig;//2

    memcpy(elem, nae->elem, min(tamElem, nae->tamElem));

    free(nae->elem);
    free(nae);

    return verdadero;
}


int ordenarLista(Lista* pl, Cmp cmp)
{
    Lista lOrd = NULL;
    Lista* plOrd;
    Nodo* nodo;

    while (*pl)
    {   //Desenganchar le nodo de la lista original
        nodo = *pl;
        *pl = nodo->sig;
        plOrd = &lOrd;

        while (*plOrd && cmp(nodo->elem, (*plOrd)->elem) > 0)
                plOrd = &(*plOrd)->sig;
        
        //Enganchar el nodo en la lista ordenada
        nodo->sig = *plOrd;
        *plOrd = nodo;
        
    }
    
    *pl = lOrd;
}
