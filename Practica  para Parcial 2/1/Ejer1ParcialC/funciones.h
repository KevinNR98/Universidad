#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#define IDXNOMB  "alumnos.idx"
#define DATNOM   "alumnos.dat"
#include "arbol.h"

typedef struct
{
    int dni;
    char apyn[40];
    int cant_materias;
    float promedio;
    char estado; ///'A' Activo - 'B' Baja
} tAlumno;


typedef struct
{
	int dni;
	int nroReg;
}tRegInd;



int cargarIndice(tArbol* arbol, const char* filename, int(*comparar)(const void*, const void*));

int compactar_indexar(tArbol* arbol, const char* filename, int(*compararDNI)(const void*, const void*));

void rotar90g_inte(tArbol* arbol, void(*accion)(const void*));

void rotar90Rec(tArbol* arbol,int nivel,void(*accion)(const void*));

void tabRec(int nivel,int cont);

void MostrarArchAlum(const char* filename);

#endif // FUNCIONES_H_INCLUDED
