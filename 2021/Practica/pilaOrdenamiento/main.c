#include <stdio.h>
#include <stdlib.h>
#include "E:\Universidad\Programacion\Librerias\Dinamica\pila\pila\pila.c"

int ordenarPila(int* datos)
{
    int num1, num2;
    tPila pila1, pila2;
    crearPila(&pila1);
    crearPila(&pila2);

    if(*datos)
    {
        ponerEnPila(&pila1, datos, sizeof(*datos));
        datos++;
    }

    while(*datos)
    {
        verTope(&pila1, &num1, sizeof(int));
        if(num1 > *datos)
        {
            while (num1 > *datos && !pilaVacia(&pila1))
            {
                sacarDePila(&pila1, &num1, sizeof(int));
                ponerEnPila(&pila2, &num1, sizeof(int));
                verTope(&pila1, &num1, sizeof(int));
            }

            ponerEnPila(&pila1, datos, sizeof(*datos));
            verTope(&pila2, &num2, sizeof(int));

            while(num2 > *datos && !pilaVacia(&pila2))
            {
                sacarDePila(&pila2, &num1, sizeof(int));
                ponerEnPila(&pila1, &num1, sizeof(int));
                verTope(&pila2, &num2, sizeof(int));
            }
        }
        else if (ponerEnPila(&pila1, datos, sizeof(*datos)))
        {
            verTope(&pila1, &num1, sizeof(int));
            datos++;
            while(num1 > *datos && !pilaVacia(&pila1))
            {
                sacarDePila(&pila1, &num1, sizeof(int));
                ponerEnPila(&pila2, &num1, sizeof(int));
                verTope(&pila1, &num1, sizeof(int));
            }

            ponerEnPila(&pila1, datos, sizeof(*datos));
            verTope(&pila2, &num2, sizeof(int));

            while(num2 > *datos && !pilaVacia(&pila2))
            {
                sacarDePila(&pila2, &num1, sizeof(int));
                ponerEnPila(&pila1, &num1, sizeof(int));
                verTope(&pila2, &num2, sizeof(int));
            }
        }
        datos++;
    }


    while(!pilaVacia(&pila1))
    {
        sacarDePila(&pila1, &num2, sizeof(int));
        printf("%d ", num2);
    }
    return 1;
}



int main()
{
    int vec[] = {3,1,5,2,6,0,4,10,7,9,8,66,34,12,156,31,11,1000,99};

    ordenarPila(vec);

    return 0;
}
