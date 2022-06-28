#ifndef TDAS_H_INCLUDED
#define TDAS_H_INCLUDED

#define TODO_OK     0
#define SIN_MEMORIA 1
#define DUPLICADO   2
#define FALSO       0
#define VERDADERO   1

#define min(x, y) ((x) < (y)? (x) : (y))

typedef int (*Cmp)(const void*, const void*);

typedef struct  Snodo
{
    void* elem;
    size_t tamElem;
    struct Snodo* hIzq;
    struct Snodo* hDer;
}NodoA;

typedef NodoA* Arbol;


typedef struct  SnodoL
{
    void* elem;
    size_t tamElem;
    struct SnodoL* sig;
    struct SnodoL* ant;
}NodoD;


typedef NodoD* ListaD;


///////////////////////////////////ARBOL BINARIO//////////////////////////////////////////
void crearArbol(Arbol* pa);
int insertarEnArbol(Arbol* pa, void* elem, size_t tamElem, Cmp cmp);
int buscarEnArbol(const Arbol* pa, void* elem, size_t tamElem, Cmp cmp);

///////////////////////////////LISTA DOBLE ENLAZADA/////////////////////////////////////////////
void crearListaD(ListaD* pl);
int insertarEnListaOrd(ListaD* pl, void* elem, size_t tamElem, Cmp cmp);




#endif // TDAS_H_INCLUDED
