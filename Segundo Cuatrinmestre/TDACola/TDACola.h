#ifndef TDACOLA_H_INCLUDED
#define TDACOLA_H_INCLUDED

#include  <stddef.h>

#include "../Comun/Comun.h"
#include "../TDACola/TDACola.h"

#if TDA_COLA_IMPL_ESTATICA
    #include "../TDAPilaImplEstatica/TDAPilaImplEstatica.h"
#else
    #include "../TDAColaImplDinamica/TDAColaImplDinamica.h"
#endif



void crearCola(Cola* pc);
boolean encolar(Cola* pc, const void* elem, size_t tamElem);
boolean desencolar(Cola* pc, void* elem, size_t tamElem);
boolean verFrenteDeCola(const Cola* pc, void* elem, size_t tamElem);
boolean colaVacia(const Cola* pc);
boolean colaLlena(const Cola*  pc, size_t tamElem);
void vaciarCola(Cola* pc);


#endif // TDACOLA_H_INCLUDED
