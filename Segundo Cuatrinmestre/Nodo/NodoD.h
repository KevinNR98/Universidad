#ifndef NODOD_H_INCLUDED
#define NODOD_H_INCLUDED


typedef struct  Snodo
{
    void* elem;
    size_t tamElem;
    struct Snodo* sig;
    struct Snodo* ant;
}NodoD;


#endif // NODOD_H_INCLUDED
