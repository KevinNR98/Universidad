#ifndef PILACIRCULAR_H_INCLUDED
#define PILACIRCULAR_H_INCLUDED
#define MINIMO(X,Y) ((X) <= (Y)?(X):(Y))

typedef struct sNodo{
void* info;
unsigned tamInfo;
struct sNodo* sig;
}tNodo;

typedef tNodo* tPila;


void crearPila(tPila* Pila);

int ponerEnPila(tPila* pila,void* dato, unsigned cantBytes);

int sacarDePila(tPila* pila,void* dato, unsigned cantBytes);

int verTope(const tPila* pila, void* dato, unsigned cantBytes);

void vaciarPila(tPila* pila);

int pilaVacia(const tPila* pila);

#endif // PILACIRCULAR_H_INCLUDED
