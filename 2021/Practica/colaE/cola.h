#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED
#define MINIMO(X,Y) ((X) < (Y)?(X):(Y))
#define TAM_COLA 24

typedef struct
{
char cola[TAM_COLA];
unsigned pri;
unsigned ult;
unsigned tamDisponible;
}tCola;

void crearCola(tCola *cola);

int ponerEnCola(tCola *cola, void *dato, unsigned cantBytes);

int sacarDeCola(tCola *cola, void *dato, unsigned cantBytes);

int colaVacia(const tCola *cola);

int colaLlena(const tCola *cola, unsigned cantBytes);

int verPrimeroCola(const tCola *cola, void *dato, unsigned cantBytes);

void vaciarCola(tCola * cola);

#endif // COLA_H_INCLUDED
