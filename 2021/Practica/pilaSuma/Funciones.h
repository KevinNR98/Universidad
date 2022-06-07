#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#define minimo(X,Y) ((X) < (Y)?(X):(Y))

typedef struct sNodo{
void* info;
unsigned tamInfo;
struct sNodo* sig;
}tNodo;

typedef tNodo* tPila;

void crearPila(tPila* Pila);

int ponerEnPila(tPila* pila, const void* dato, unsigned cantBytes);

int pilaLlena(const tPila* pila, unsigned cantBytes);

int verTope(const tPila *pila, void *dato, unsigned cantBytes);

int pilaVacia(const tPila *pila);

void vaciarPila(tPila *pila);

int sacarDePila(tPila *pila, void *dato, unsigned cantBytes);


#endif // FUNCIONES_H_INCLUDED
