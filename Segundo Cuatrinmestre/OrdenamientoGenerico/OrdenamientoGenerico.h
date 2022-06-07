#ifndef ORDENAMIENTOGENERICO_H_INCLUDED
#define ORDENAMIENTOGENERICO_H_INCLUDED

typedef int (*Cmp)(const void*, const void*);
typedef void (*Mostrar)(const void*);

void ordenarGenBurbujeo(void* vector, int ce, size_t tamElem, Cmp cmp);
void ordenarGenSeleccion(void* vector, int ce, size_t tamElem, Cmp cmp);
void ordenarGenInsercion(void* vector, int ce, size_t tamElem, Cmp cmp);

void mostrarVectorGen(void* vector, int ce, size_t tamElem, Mostrar mostrar);


#endif // ORDENAMIENTOGENERICO_H_INCLUDED
