#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#define ARCH_ALUM "alumnos.dat"
#define ARCH_IDX  "alumnos.idx"
#define MINIMO(X,Y) ((X) < (Y)? (X):(Y))
#include "Arbol.h"


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
    int nro_reg;
} tRegInd;


void MostrarArchAlum(const char* filename);

int cmpDni(const void* a, const void* b);

void mostrarIndice(const void* a);

void MostrarArbol(tArbol* arbol, void(*accion)(const void*));

void ingresarDniAlumn(tAlumno* alumno);

int baja(tArbol* arbol, int dni, int(*cmpDni)(const void*, const void*));

#endif // FUNCIONES_H_INCLUDED
