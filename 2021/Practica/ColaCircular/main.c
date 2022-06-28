#include <stdio.h>
#include <stdlib.h>
#include "ColaCircular.h"
#define TAM 10

int main()
{
    int vec[TAM] = {1,2,3,4,5,6,7,8,9,10};
    int num;
    tCola cola;
    crearCola(&cola);

    for(int i = 0; i <  TAM; i++)
    {
        ponerEnCola(&cola, &vec[i],sizeof(int));
    }

    while(!colaVacia(&cola))
    {
        sacarDeCola(&cola, &num,sizeof(int));
        printf("%d\n", num);
    }
    return 0;
}
