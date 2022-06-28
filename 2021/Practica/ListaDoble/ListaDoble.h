#ifndef LISTADOBLE_H_INCLUDED
#define LISTADOBLE_H_INCLUDED
#define MINIMO(x,y) (x)<(y)?(x):(y)

typedef struct Snodo{
void* info;
unsigned tamInfo;
struct Snodo *sig;
struct Snodo *ant;
}tNodo;

typedef tNodo* tLista;

void creaLista(tLista* lista);

int listaVacia(const tLista* lista);

int vaciarLista(tLista* lista);

int listaLlena(const tLista* lista, unsigned cantBytes);

int insertarAlInicio(tLista* lista, void* dato, unsigned cantBytes);

int insertarAlFinal(tLista* lista, void* dato, unsigned cantBytes);

int insertarEnListaOrdenado(tLista* lista, void* dato, unsigned cantBytes, int(*comparar)(const void*, const void*));

int eliminarPorClave(tLista* lista, void* dato, unsigned cantBytes, int(*comparar)(const void*, const void*));

void recorrerListaIzq(tLista* lista, void(*accion)(const void*));

void recorrerListaDer(tLista* lista, void(*accion)(const void*));

void ordenarLista(tLista* lista, int(*comparar)(const void*, const void*));

tLista* buscarMenor(tLista* lista, int(*comparar)(const void*, const void*));

#endif // LISTADOBLE_H_INCLUDED
