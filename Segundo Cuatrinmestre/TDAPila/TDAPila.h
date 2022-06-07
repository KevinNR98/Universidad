//#ifndef TDAPILA_H_INCLUDED
#define TDAPILA_H_INCLUDED

#include <stddef.h>

#include "../Comun/Comun.h"

#ifdef TDA_PILA_IMPL_ESTATICA
#include "../TDAPilaImpEstatica/TDAPilaImplEstatica.h"
#else
#include "../TDAPilaImpDinamica/TDAPilaImpDinamica.h"



void crearPila(Pila* pp);
boolean apilar(Pila* pp, const void* elem, size_t tamElem);
boolean desapilar(Pila* pp, void * elem, size_t tamElem);
boolean verTopePila(const Pila* pp, void * elem, size_t tamElem);
boolean pilaVacia(const Pila* pp);
boolean pilaLlena(const Pila* pp, size_t tamElem);
void vaciarPila(Pila* pp);

#endif // TDAPILA_H_INCLUDED
