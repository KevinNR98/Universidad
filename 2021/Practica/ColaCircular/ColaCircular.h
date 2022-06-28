#ifndef COLACIRCULAR_H_INCLUDED
#define COLACIRCULAR_H_INCLUDED
#define MINIMO(X,Y) ((X) < (Y)?(X):(Y))


typedef struct Snodo{
void* info;
unsigned tamInfo;
struct Snodo* sig;
}tNodo;

typedef tNodo* tCola;


void crearCola(tCola* cola);

int ponerEnCola(tCola* cola, void* dato, unsigned cantBytes);

int sacarDeCola(tCola* cola, void* dato, unsigned cantBytes);

int colaVacia(const tCola* cola);


#endif // COLACIRCULAR_H_INCLUDED
