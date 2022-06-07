#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

typedef struct  Snodo
{
    void* elem;
    size_t tamElem;
    struct Snodo* sig;
}Nodo;


#endif // NODO_H_INCLUDED
