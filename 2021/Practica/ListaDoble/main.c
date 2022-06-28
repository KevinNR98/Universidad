#include <stdio.h>
#include <stdlib.h>
#include "ListaDoble.h"

int comparar(const void*, const void*);

void accion(const void*);

int acumuladorCantidad(void** info, unsigned* tam, const void* dato, unsigned cantBytes);

int main()
{
    int vec[11] = {1,3,5,15,36,0,78,10,14,30,100};
    int valor = 100;
    tLista lista;
    creaLista(&lista);

    for(int i = 0; i < 11; i++)
    {
        insertarAlFinal(&lista, &vec[i],sizeof(int));
//        insertarAlInicio(&lista, &vec[i],sizeof(int));
//        insertarEnListaOrdenado(&lista, &vec[i],sizeof(int),comparar);
    }
    recorrerListaIzq(&lista,accion);
    vaciarLista(&lista);
//    vaciarListaRecur(&lista);
    puts("///////////////");
    recorrerListaIzq(&lista,accion);
//    eliminarPorClave(&lista,&valor,sizeof(int),comparar);
    puts("///////////////");
//    ordenarLista(&lista, comparar);
//    recorrerListaIzq(&lista,accion);

//    recorrerLista(&lista,accion);

}


int comparar(const void* cmp1, const void* cmp2)
{
    return *(int*) cmp1 - *(int*)cmp2;
}


void accion(const void*a)
{
    printf("%d\n",*(int*)a);
}



int acumuladorCantidad(void** info, unsigned* tam, const void* dato, unsigned cantBytes)
{
    tArmadoYRep **cant1 = (tArmadoYRep**)info;
    tArmadoYRep *cant2 = (tArmadoYRep*)dato;
    (*cant1)->cantidad += cant2->cantidad;
    return 1;
}
