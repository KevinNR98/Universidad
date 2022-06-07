#ifndef NODOA_H_INCLUDED
#define NODOA_H_INCLUDED

typedef struct  Snodo
{
    void* elem;
    size_t tamElem;
    struct Snodo* hIzq;
    struct Snodo* hDer;
}NodoA;

#endif // NODOA_H_INCLUDED
