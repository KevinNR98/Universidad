#ifndef ESTATICA_H_INCLUDED
#define ESTATICA_H_INCLUDED
#define minimo(X,Y) ((X) <= (Y)?(X):(Y))
#define TAM_PILA  340

typedef struct{
char pila[TAM_PILA];
unsigned tope;
}tPila;

void crearPila(tPila *pila);

int pilaLlena(const tPila *pila, unsigned cantBytes);

int ponerEnPila(tPila *pila, const void *dato, unsigned cantBytes);

int verTope(const tPila *pila, void *dato, unsigned cantBytes);

int pilaVacia(const tPila *pila);

void vaciarPila(tPila *pila);

int sacarDePila(tPila *pila, void *dato, unsigned cantBytes);


#endif // ESTATICA_H_INCLUDED
