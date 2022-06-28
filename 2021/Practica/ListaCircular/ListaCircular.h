#ifndef LISTACIRCULAR_H_INCLUDED
#define LISTACIRCULAR_H_INCLUDED

typedef struct Snodo{
void* info;
unsigned tamInfo;
struct Snodo* sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* lista);

int insertarAlPrincipio(tLista* lista, void* dato, unsigned cantBytes);

int insertarAlFinal(tLista* lista, void* dato, unsigned cantBytes);

void recorrerLista(tLista* lista, void(*accion)(const void*));

#endif // LISTACIRCULAR_H_INCLUDED
