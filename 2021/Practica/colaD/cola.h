#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED
#define minimo(X,Y) ((X) < (Y)?(X):(Y))

typedef struct sNodo{
void* info;
unsigned tamInfo;
struct sNodo* sig;
}tNodo;

typedef struct{
tNodo* pri;
tNodo* ult;
}tCola;

void crearCola(tCola* cola);

int colaVacia(const tCola* cola);

int colaLlena(const tCola* cola, unsigned cantBytes);

int ponerEnCola(tCola *cola, void* dato, unsigned cantBytes);

int sacarDeCola(tCola* cola, void* dato, unsigned cantBytes);

void vaciarCola(tCola *cola);

int verPrimero(const tCola *cola, void* dato, unsigned cantBytes);


#endif // COLA_H_INCLUDED
