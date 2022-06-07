#include <stdio.h>
#include "Vectores.h"

void crearVector(Vector* vec, size_t tamElem)
{
    vec->cantElem = 0;
    vec->tamElem = tamElem;
}


int insertarEnVectorOrdSinDup(Vector* vec, int elem)
{
    int posIns;

    if(vec->cantElem == TAM)
        return VEC_LLENO;

    int posAct = 0;

    while(posAct < vec->cantElem && elem > vec->v[posAct])
        posAct++;


    if(posAct < vec->cantElem && elem == vec->v[posAct])/// tengo que asegurarme de que posAct apunte a un elemneto valido que este dentro del vector
        return DUPLICADO;

    posIns = posAct;

    for(posAct = vec->cantElem - 1; posAct >= posIns; posAct--)
        vec->v[posAct + 1] = vec->v[posAct];

    vec->v[posIns] = elem;

    vec->cantElem++;

    return TODO_OK;
}


int insertarEnVectorOrdConDup(Vector* vec, int elem)
{
    if(vec->cantElem == TAM)
        return VEC_LLENO;

    int posAct = vec->cantElem - 1;

    while(posAct >= 0 && elem < vec->v[posAct])
    {
        vec->v[posAct + 1] = vec->v[posAct];
        posAct--;
    }

    vec->v[posAct + 1] = elem;
    vec->cantElem++;

    return TODO_OK;
}

boolean eliminarDeVectorOrd(Vector* vec, int elem)
{
    int posAct = 0;

    while(posAct < vec->cantElem && elem > vec->v[posAct])
    {
        posAct++;
    }

    if(posAct == vec->cantElem || elem < vec->v[posAct])
        return falso;


    for( ; posAct <= vec->cantElem - 2; posAct++)
    {
        vec->v[posAct] = vec->v[posAct + 1];
    }

    vec->cantElem--;

    return verdadero;
}

boolean eliminarDeVectorDesord(Vector* vec, int elem)
{

}

boolean eliminarDeVector(Vector* vec, int elem)/// sirve tanto como para vectores ordenados y desordenados.
{
    int orig, dest;
    int cantElim;

    orig = dest = 0;

    while(orig < vec->cantElem)
    {
        if(vec->v[orig] != elem)
        {
            if(orig != dest)
                vec->v[dest] = vec->v[orig];

            dest++;
        }

        orig++;
    }

    cantElim = vec->cantElem - dest;
    vec->cantElem = dest;

    return cantElim;
}

int insertarEnVectorAlFinal(Vector* vec, int elem)
{
    if(vec->cantElem == TAM)
        return VEC_LLENO;

    vec->v[vec->cantElem] = elem;

    vec->cantElem++;

    return TODO_OK;
}

void mostrarVector(const Vector* vec)
{
    if(vec->cantElem == 0)
    {
        puts("El vector esta vacio.");
        return;
    }

    for(int i = 0; i < vec->cantElem; i++)
        printf("[%d] ", vec->v[i]);

    putchar('\n');
}


//void ordenarVecSeleccion()
//{
//    void*///reveer la parte del video
//}

//boolean buscarEnVectorOrd(const Vector* vec, int elem)
//{
//
//}



void ordenarGenBurbujeo(int* Vector, int cantElem)
{
    int ordenado = 0, aux;

    while (!ordenado)
    {
        ordenado = 1;
        for(int i = 0; i < cantElem - 1; i++)
        {
            if(Vector[i] > Vector[i + 1])
            {
                aux = Vector[i];
                Vector[i] = Vector[i + 1];
                Vector[i + 1] = aux;
                ordenado = 0;
            }
        }
    }
}

//////////////////////////////////INVESTIGAR FUNCION RAND, SRAND Y TIME PARA CALCULAR EL TIEMPO DE EJECUCION DE UNA FUNCION.
