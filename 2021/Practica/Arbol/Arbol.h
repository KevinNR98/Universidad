#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#define MINIMO(X,Y) ((X) < (Y)? (X):(Y))

typedef struct SnodoArbol{
void* info;
unsigned tamInfo;
struct SnodoArbol* der;
struct SnodoArbol* izq;
}tNodoArbol;

typedef tNodoArbol* tArbol;

void crearArbol(tArbol* arbol);

int R_insertarEnArbol(tArbol* arbol, void* dato, unsigned cantBytes, int(*comparar)(const void*, const void*));

void recorrerArbolPreOrden(tArbol* arbol, void(*accion)(const void*));

void recorrerArbolInOrden(tArbol* arbol, void(*accion)(const void*));

void recorrerArbolPosOrden(tArbol* arbol, void(*accion)(const void*));

void rotarArbol(tArbol* arbol, void(*accion)(const void*, unsigned), unsigned nivel);

void rotarArbol_90g(tArbol* arbol, void(*accion)(const void*, unsigned), unsigned nivel);

unsigned contarNodos(const tArbol* arbol);

int alturaArbol(tArbol* arbol);

int esCompleto(tArbol* arbol);

int esBalanceado(tArbol* arbol);

int esCompleto_aNiv(tArbol* arbol, int nivel);

int esAVL(tArbol* arbol);

int eliminarNodoRaiz(tArbol* arbol);

tArbol* menorNodoArbIzq(const tArbol* arbol);

tArbol* mayorNodoArbDer(const tArbol* arbol);

int eliminarElemArbol(tArbol* arbol, void* dato, unsigned cantBytes, int(*comparar)(const void*, const void*));

tNodoArbol** buscarNodoArbol(const tArbol* arbol, void* dato,int(*comparar)(const void*, const void*));


#endif // ARBOL_H_INCLUDED
