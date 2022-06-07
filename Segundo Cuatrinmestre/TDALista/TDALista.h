#ifndef TDALISTA_H_INCLUDED
#define TDALISTA_H_INCLUDED

#include <stddef.h>

#include "../Comun/Comun.h"

#ifdef TDA_LISTA_IMPL_DINAMICA
    #include "../TDAListaImplDinamica/TDAListaImplDinamica.h"
#endif

#ifdef TDA_LISTA_IMPL_DINAMICA_DOBLE
    #include "../TDAListaImplDinamicaDoble/TDAListaImplDinamicaDoble.h"
#endif

#ifdef TDA_LISTA_IMPL_DINAMICA_CIRCULAR
    #include"../TDAListaImplDinamicaCircular/TDAListaImplDinamicaCircular.h"
#endif



void crearLista(Lista* pl);
boolean listaVacia(const Lista* pl);
boolean listaLlena(Lista* pl);
int insertarEnListaOrd(Lista* pl, void* elem, size_t tamElem, Cmp cmp);
int insertarActualizarEnListaOrd(Lista* pl, void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar);
int insertarEnListaEnPosicion(Lista* pl, void* elem, size_t tamElem, unsigned pos);
int insertarEnListaAlFinal(Lista* pl, void* elem, size_t tamElem);
int insertarEnListaAlInicio(Lista* pl, void* elem, size_t tamElem);
boolean buscarEnListaOrd(Lista* pl, void* elem, size_t tamElem, Cmp cmp);
boolean buscarEnListaDesord(Lista* pl, void* elem, size_t tamElem, Cmp cmp);
boolean eliminarDeListaOrd(Lista* pl, void* elem, size_t tamElem, Cmp cmp);
boolean eliminarDeListaDesord(Lista* pl, void* elem, size_t tamElem, Cmp cmp);
boolean eliminarDeListaDePosicion(Lista* pl, void* elem, size_t tamElem, Cmp cmp);
int eliminarDuplicadosDeListaOrd(Lista* pl, Cmp cmp, Actualizar actualizar);
int eliminarDuplicadosDeListaDesord(Lista* pl, Cmp cmp, Actualizar actualizar);
int ordenarLista(Lista* pl, Cmp cmp);
boolean vaciarLista(Lista* pl);

#endif // TDALISTA_H_INCLUDED
