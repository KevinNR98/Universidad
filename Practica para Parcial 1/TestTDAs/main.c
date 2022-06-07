#include <stdio.h>
#include <stdlib.h>
#include "tda.h"

int cmpNumeros(const void* a, const void* b);

int main()
{
//    Pila enteros;
//    PilaEs enteros;
//    Cola enteros;
//    ColaEs enteros;
    Lista enteros;

//    crearPila(&enteros);
//    crearPilaEs(&enteros);
//    crearCola(&enteros);
//    crearColaEs(&enteros);
    crearLista(&enteros);

    int num = 5;
    int num1 = 7;
    int num2 = 9;
    int num3 = 10;
    int num4 = 55;



//    apilar(&enteros, &num, sizeof(int));
//    apilar(&enteros, &num1, sizeof(int));
//    apilar(&enteros, &num2, sizeof(int));
//    apilar(&enteros, &num3, sizeof(int));
//    apilar(&enteros, &num4, sizeof(int));

//    apilarEs(&enteros, &num, sizeof(int));
//    apilarEs(&enteros, &num1, sizeof(int));
//    apilarEs(&enteros, &num2, sizeof(int));
//    apilarEs(&enteros, &num3, sizeof(int));
//    apilarEs(&enteros, &num4, sizeof(int));

//    encolar(&enteros, &num, sizeof(int));
//    encolar(&enteros, &num1, sizeof(int));
//    encolar(&enteros, &num2, sizeof(int));
//    encolar(&enteros, &num3, sizeof(int));
//    encolar(&enteros, &num4, sizeof(int));

//    encolarEs(&enteros, &num, sizeof(int));
//    encolarEs(&enteros, &num1, sizeof(int));
//    encolarEs(&enteros, &num2, sizeof(int));
//    encolarEs(&enteros, &num3, sizeof(int));
//    encolarEs(&enteros, &num4, sizeof(int));

    insertarEnListaOrd(&enteros, &num, sizeof(int), cmpNumeros);
    insertarEnListaOrd(&enteros, &num1, sizeof(int), cmpNumeros);
    insertarEnListaOrd(&enteros, &num2, sizeof(int), cmpNumeros);
    insertarEnListaOrd(&enteros, &num3, sizeof(int), cmpNumeros);
    insertarEnListaOrd(&enteros, &num4, sizeof(int), cmpNumeros);


//
//    while(!pilaVacia(&enteros))
//    {
//        desapilar(&enteros, &num, sizeof(int));
//        printf("%d\n", num);
//    }


//    while(!pilaVaciaEs(&enteros))
//    {
//        desapilarEs(&enteros, &num, sizeof(int));
//        printf("%d\n", num);
//    }

//
//    while(!colaVacia(&enteros))
//    {
//        desencolar(&enteros, &num, sizeof(int));
//        printf("%d\n", num);
//    }
//
//
//    while(!colaVaciaEs(&enteros))
//    {
//        desencolarEs(&enteros, &num, sizeof(int));
//        printf("%d\n", num);
//    }

    int bus = 16;
    int ret = 0;

    ret = buscarEnListaOrd(&enteros, &bus, sizeof(int), cmpNumeros);
    if(ret)
        printf("%d\n", bus);
    else
        printf("No se encontro el valor");
    sacarDeListaOrd(&enteros, &num, sizeof(int), cmpNumeros);
    printf("%d\n", num);
    sacarDeListaOrd(&enteros, &num2, sizeof(int), cmpNumeros);
    printf("%d\n", num2);
    sacarDeListaOrd(&enteros, &num1, sizeof(int), cmpNumeros);
    printf("%d\n", num1);
    sacarDeListaOrd(&enteros, &num4, sizeof(int), cmpNumeros);
    printf("%d\n", num4);
    sacarDeListaOrd(&enteros, &num3, sizeof(int), cmpNumeros);
    printf("%d\n", num3);




    return 0;
}


int cmpNumeros(const void* a, const void* b)
{
    return (*(int*)a) - (*(int*)b);
}
