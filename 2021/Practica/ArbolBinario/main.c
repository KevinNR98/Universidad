#include <stdio.h>
#include <stdlib.h>
#include "ArbolBinario.h"
#include "utils/utils.h"

int comparar(const void*, const void*);

void mostrarEntero(const void*);

void mostrarRotado_90g(const void*, unsigned);

void imprimirArbol(const void*, unsigned);

int main()
{
    const char* filename = "indice.dat";
    int clave = 25;
    tArbol arbolito;
    tArbol arbol;
//    int vec[] = {100,50,25,10,30,75,150,175};
    int vec[] = {100,50,25,75,120,119,135,140,144};
//    int vec2[]={10,25,75,120,100,130,};

    crearArbol(&arbolito);
    crearArbol(&arbol);

    for(int i = 0; i < sizeof(vec)/sizeof(int); i++)
    {
        R_insertarEnArbol(&arbolito,&vec[i],sizeof(int), comparar);
//        R_insertarEnArbol(&arbol,&vec2[i],sizeof(int),comparar);
    }

//    recorrerArbolInOrden(&arbolito, mostrarEntero);
//    recorrerArbolPreOrden(&arbolito, mostrarEntero);
    rotarArbol(&arbolito, mostrarRotado_90g,0);
    puts("/////////");
    printf("%d\n", contarNodos(&arbolito));
    puts("/////////");
    printf("%d\n", alturaArbol(&arbolito));
    puts("/////////");
//    printf("%d\n", esCompleto_aNiv(&arbolito, 2));
    puts("/////////");
    printf("%d\n", esCompleto(&arbolito));
    puts("/////////");
    printf("%d\n", esBalanceado(&arbolito));
    puts("/////////");
    printf("%d\n", esAVL(&arbolito));
    puts("/////////");

//    eliminarNodoRaiz(&arbolito);
    eliminarElemArbol(&arbolito,&clave,sizeof(int),comparar);
    rotarArbol(&arbolito, mostrarRotado_90g,0);


//   rotarArbol_90g(&arbol, mostrarRotado_90g,0);
//    rotarArbol(&arbolito,mostrarRotado_90g,0);

    createBigFile(filename, 15);

    return 0;
}


int comparar(const void* cmp1, const void* cmp2)
{
    return *(int*) cmp1 - *(int*)cmp2;
}


void mostrarEntero(const void*a)
{
    printf("%d\n",*(int*)a);
}


void mostrarRotado_90g(const void* a, unsigned n)
{
    printf("%*d\n", 6*n,*(int*)a);
}







////////////////////////EJER TIPO PARCIAL//////////////////////////////////////////


