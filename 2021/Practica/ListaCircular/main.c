#include <stdio.h>
#include <stdlib.h>
#include "ListaCircular.h"

void accion(const void*);


int main()
{
    int vec[10] = {0,1,2,3,4,5,6,7,8,9};
    tLista lista;
    crearLista(&lista);

    for(int i = 0; i < 10; i++)
    {
        insertarAlFinal(&lista,&vec[i],sizeof(int));
//        insertarAlPrincipio(&lista,&vec[i],sizeof(int));
    }

    recorrerLista(&lista, accion);

}


void accion(const void*a)
{
    printf("%d\n",*(int*)a);
}
