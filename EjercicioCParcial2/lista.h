#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#define MINIMO(X,Y) ((X) < (Y)?(X):(Y))


typedef struct Snodo{
void* info;
unsigned tamInfo;
struct Snodo *sig;
struct Snodo *ant;
}tNodo;

typedef tNodo* tLista;

void creaLista(tLista* lista);

int insertarEnListaOrdenadoYacum(tLista* lista, void* dato, unsigned cantBytes, int(*comparar)(const void*, const void*),int(*acum)(void**, unsigned*, const void*, unsigned));

void recorrerListaDer(tLista* lista, void(*accion)(const void*));

//typedef struct sNodo{
//void* info;
//unsigned tamInfo;
//struct sNodo* sig;
//}tNodo;
//
//typedef tNodo* tLista;
//
//void crearListaS(tLista* lista);
//
//int insertarOrdenadoRecur(tLista* lista, void* dato, int(*comparar)(const void*, const void*), unsigned cantBytes, int duplicado);
//
//void R_recorrerLista(tLista* lista, void(*accion)(const void*));

#endif // LISTA_H_INCLUDED
