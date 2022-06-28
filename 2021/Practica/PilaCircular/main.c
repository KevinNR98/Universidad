#include <stdio.h>
#include <stdlib.h>
#include "PilaCircular.h"
#define TAM 10

int main()
{
    int vec[TAM] = {1,2,3,4,5,6,7,8,9,10};
    int num;
    tPila pila;
    crearPila(&pila);

    for(int i = 0; i <  TAM; i++)
    {
        ponerEnPila(&pila, &vec[i],sizeof(int));
    }

    while(!pilaVacia(&pila))
    {
        sacarDePila(&pila, &num,sizeof(int));
        printf("%d\n", num);
    }

    return 0;
}
