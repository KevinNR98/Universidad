#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#include "../TDALista/TDALista.h"

void crearLista(Lista *pl)
{
    *pl = NULL;
}

boolean listaVacia(const Lista *pl)
{
    return *pl = NULL;
}

int insertarEnListaOrd(Lista *pl, void *elem, size_t tamElem, Cmp cmp)
{
    NodoD *act = *pl, *ant, *sig;

    if (!act)
    {
        ant = sig = NULL;
    }
    else
    {
        while (act->ant && cmp(elem, act->elem) < 0) //Avanzo hacia la izquierda
            act = act->ant;

        while (act->sig && cmp(elem, act->elem) > 0) //Avanzo hacia la derecha
            act = act->sig;


        int comp = cmp(elem, act->elem);

        if (comp == 0) //Si ya exisye no lo inserto
            return DUPLICADO;

        if(comp < 0)
        {
            sig = act;
            ant = act->ant;
        }
        else
        {
            ant = act;
            sig = act->sig;
        }
    }

    NodoD* nuevo = malloc(sizeof(NodoD));
    void* nuevoElem = malloc(tamElem);

    if(!nuevo || !nuevoElem)
    {
        free(nuevo);
        free(nuevoElem);
        return SIN_MEMORIA;
    }

    memcpy(nuevoElem, elem, tamElem);
    nuevo->elem = nuevoElem;
    nuevo->tamElem = tamElem;

    nuevo->ant = ant;//1
    nuevo->sig = sig;//2

    if(ant)
        ant->sig = nuevo;//3
    
    if(sig)
        sig->ant = nuevo;
    
    *pl = nuevo;

    return TODO_OK;
}