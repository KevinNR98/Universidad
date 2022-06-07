#include <stdio.h>
#include <memory.h>
#include "OrdenamientoGenerico.h"

void intercambiar(void* a, void* b, size_t tamElem);
void* buscarMenor(void* inicio, void* fin, size_t tamElem, Cmp cmp);

//void ordenarGenBurbujeo(void* vector, int ce, size_t tamElem, Cmp cmp)
//{
//    int ordenado = 0;
//
//    while (!ordenado)
//    {
//        ordenado = 1;
//        for (int i = 0; i < ce - 1; i++)
//        {
//            if (vector[i] > vector[i + 1])
//            {
//                intercambiar(&vector[i], &vector[i + 1]);
//                ordenado = 0;
//            }
//        }
//    }
//}



void ordenarGenSeleccion(void* vector, int ce, size_t tamElem, Cmp cmp)
{
    void* i, *menor;
    void* ultimo = vector + (ce - 1) * tamElem;

    for(i = vector; i < ultimo; i += tamElem)
    {
        menor = buscarMenor(i, ultimo, tamElem, cmp);
        if(menor != i)
            intercambiar(i, menor, tamElem);
    }
}


void ordenarGenInsercion(void* vector, int ce, size_t tamElem, Cmp cmp);


void* buscarMenor(void* inicio, void* fin, size_t tamElem, Cmp cmp)
{
    void* j, *menor;
    menor = inicio;

    for (j = inicio + tamElem; j <= fin; j += tamElem)
    {
        if (cmp(j, menor) < 0)
            menor = j;
    }
    return menor;
}


void intercambiar(void* a, void* b, size_t tamElem)
{
    char aux[tamElem];
 //   void* aux = malloc(tamElem);

    memcpy(aux, a, tamElem); // aux = a
    memcpy(a, b, tamElem); // a = b
    memcpy(b, aux, tamElem); // b = aux
 //   free(aux);
}


void mostrarVectorGen(void* vector, int ce, size_t tamElem, Mostrar mostrar)
{
    void* ultimo = vector + (ce - 1) * tamElem;

    for(void* i = vector; i <= ultimo; i += tamElem)
    {
        mostrar(i);
        putchar(' ');
    }
}

