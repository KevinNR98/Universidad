#ifndef TDAARBOL_H_INCLUDED
#define TDAARBOL_H_INCLUDED

#include "../Comun/Comun.h"

#ifdef TDA_ARBOL_IMPL_DINAMICA
    #include "../TDAArbolImplDinamica/TDAArbolImplDinamica.h"
#endif


void crearArbol(Arbol* pa);
int insertarEnArbol(Arbol* pa, const void* elem, size_t tamElem, Cmp cmp);
boolean buscarEnArbol(const Arbol* pa, void* elem, size_t tamElem, Cmp cmp);
boolean eliminarDeArbol(const Arbol* pa, void* elem, size_t tamElem, Cmp cmp);
void vacairArbol(Arbol* pa);
boolean esArbolVacio(const Arbol* pa);
boolean esArbolLleno(const Arbol* pa);
int alturaArbol(const Arbol* pa);
int podarArbol(Arbol* pa, int nivel);
int contarElemntosArbol(const Arbol* pa);
int contarHojasArbol(const Arbol* pa);
void recorrerArbolPreOrden(const Arbol* pa, Accion accion, void* datosAccion);//RID
void recorrerArbolEnOrden(const Arbol* pa, Accion accion, void* datosAccion);//IRD
void recorrerArbolPosOrden(const Arbol* pa, Accion accion, void* datosAccion);//IDR
boolean esArbolCompleto(const Arbol* pa);///Contiene todos los elementos posibles
boolean esArbolBalanceado(const Arbol* pa);///Completo hasta el penultimo nivel
boolean esArbolAVL(const Arbol* pa);// Dif de altura entre los dos hijos de un nodo no puede ser mayor que 1

#endif // TDAARBOL_H_INCLUDED
