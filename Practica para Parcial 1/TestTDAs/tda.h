#ifndef TDA_H_INCLUDED
#define TDA_H_INCLUDED

#define TODO_OK     0
#define ERROR       1
#define SIN_MEMORIA 1
#define DUPLICADO   1

#define TAM_PILA    5000
#define TAM_COLA    5000

#define min(x, y) ((x) < (y)? (x) : (y))

typedef int (*Cmp)(const void* a, const void* b);

typedef struct sNodo
{
    void* elem;
    size_t tamElem;
    struct sNodo* sig;
}Nodo;

typedef struct
{
    char vPila[TAM_PILA];
    size_t tope;
}PilaEs;

typedef Nodo* Pila;

typedef struct
{
    Nodo* frente;
    Nodo* fondo;
}Cola;

typedef struct
{
    char vCola[TAM_COLA];
    char* frente;
    char* fondo;
    size_t tamDisponible;
}ColaEs;

typedef Nodo* Lista;

////////////////////PILA DINAMICA///////////////////
void crearPila(Pila* pila);
int apilar(Pila* pila, const void* elem, size_t tamElem);
int desapilar(Pila* pila, void* elem, size_t tamElem);
int verTopePila(Pila* pila, void* elem, size_t tamElem);
int pilaLlena(Pila* pila, size_t tamElem);
int pilaVacia(Pila* pila);
void vaciarPila(Pila* pila);


//////////////////PILA ESTATICA///////////////////////
void crearPilaEs(PilaEs* pila);
int apilarEs(PilaEs* pila, const void* elem, size_t tamElem);
int desapilarEs(PilaEs* pila, void* elem, size_t tamElem);
int verTopePilaEs(PilaEs* pila, void* elem, size_t tamElem);
int pilaLlenaEs(PilaEs* pila, size_t tamElem);
int pilaVaciaEs(PilaEs* pila);
void vaciarPilaEs(PilaEs* pila);

///////////////////COLA DINAMICA//////////////////////
void crearCola(Cola* cola);
int encolar(Cola* cola, const void* elem, size_t tamElem);
int desencolar(Cola* cola, void* elem, size_t tamElem);
int verFrenteCola(Cola* cola, void* elem, size_t tamElem);
int verFondoCola(Cola* cola, const void* elem, size_t tamElem);
int colaLlena(const Cola* cola, size_t tamElem);
int colaVacia(const Cola* cola);
void vaciarCola(Cola* cola);

///////////////////COLA ESTATICA//////////////////////
void crearColaEs(ColaEs* cola);
int encolarEs(ColaEs* cola, const void* elem, size_t tamElem);
char* copiarAVector(char* vecLIzq, char* vecLDer, char* iniCopia, void* elem, size_t tamElem);
int desencolarEs(ColaEs* cola, void* elem, size_t tamElem);
char* copiarDeVector(char* vecLIzq, char* vecLDer, char* iniCopia, void* elem, size_t tamElem, size_t tamElemEncolado);
int verFrenteColaEs(ColaEs* cola, void* elem, size_t tamElem);
int verFondoColoEs(ColaEs* cola, const void* elem, size_t tamElem);
int colaLlenaEs(const ColaEs* cola, size_t tamElem);
int colaVaciaEs(const ColaEs* cola);
void vaciarColaEs(ColaEs* cola);

////////////////LISTA SIMPLEMENTE ENLAZADA DINAMICA//////////
void crearLista(Lista* lista);
int insertarEnListaOrd(Lista* lista, const void* elem, size_t tamElem, Cmp cmp);
int sacarDeListaOrd(Lista* lista, void* elem, size_t tamElem, Cmp cmp);
int buscarEnListaOrd(Lista* lista, void* elem, size_t tamElem, Cmp cmp);
int ordenarLista(Lista* lista, Cmp cmp);
int listaVacia(Lista* lista);
int listaLlena(Lista* lista, size_t tamElem);
void vaciarLista(Lista* lista);



#endif // TDA_H_INCLUDED
