#ifndef VECTORES_H_INCLUDED
#define VECTORES_H_INCLUDED
#include "../Comun/Comun.h"
#include "../Fecha/Fecha.h"

#define TAM 10
#define TODO_OK 0
#define VEC_LLENO 1
#define DUPLICADO 2

typedef struct
{
    int dni;
    char apyn[101];
    Fecha fechaNac;
    float sueldo;
}Empleado;

typedef struct
{
    char v[TAM];
    int cantElem;
    size_t tamElem;
}Vector;



void crearVector(Vector* vec, size_t tamElem);

int insertarEnVectorOrdSinDup(Vector* vec, int elem);

int insertarEnVectorOrdConDup(Vector* vec, int elem);

boolean eliminarDeVectorOrd(Vector* vec, int elem);

boolean eliminarDeVectorDesord(Vector* vec, int elem);

boolean buscarEnVectorOrd(const Vector* vec, int elem);

boolean buscarEnVectorDesord(const Vector* vec, int elem);

void odenarVec(Vector* vec);

void mostrarVector(const Vector* vec);

boolean eliminarDeVector(Vector* vec, int elem);

int insertarEnVectorAlFinal(Vector* vec, int elem);

void ordenarGenBurbujeo(int* Vector, int cantElem);


#endif // VECTORES_H_INCLUDED
