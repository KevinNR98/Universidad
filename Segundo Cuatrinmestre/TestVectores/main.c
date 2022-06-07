#include <stdio.h>
#include <stdlib.h>
#include "../vectores/vectores.h"

void mostrarCodigo(int codigo);

int main()
{
    Vector vec;
    int ret, cantElim;
    int numeros[10] = {9, 3, 6, 2, 1, 4, 5, 7, 8, 10};

    crearVector(&vec, sizeof(Empleado));

//    mostrarVector(&vec);
//
//    insertarEnVectorOrdConDup(&vec, 9);
//    mostrarVector(&vec);
//
//    insertarEnVectorOrdConDup(&vec, 15);
//    mostrarVector(&vec);
//
//    insertarEnVectorOrdConDup(&vec, 11);
//    mostrarVector(&vec);
//
//    insertarEnVectorOrdConDup(&vec, 1);
//    mostrarVector(&vec);

//    insertarEnVectorOrdConDup(&vec, 1);
//    mostrarVector(&vec);


//    mostrarVector(&vec);
//
//    ret = insertarEnVectorOrdSinDup(&vec, 9);
//    mostrarCodigo(ret);
//    mostrarVector(&vec);
//
//    ret = insertarEnVectorOrdSinDup(&vec, 15);
//    mostrarCodigo(ret);
//    mostrarVector(&vec);
//
//    ret = insertarEnVectorOrdSinDup(&vec, 11);
//    mostrarCodigo(ret);
//    mostrarVector(&vec);
//
//    ret = insertarEnVectorOrdSinDup(&vec, 20);
//    mostrarCodigo(ret);
//    mostrarVector(&vec);
//
//    ret = insertarEnVectorOrdSinDup(&vec, 15);
//    mostrarCodigo(ret);
//    mostrarVector(&vec);
//
//    int elemento = 11;
//
//    boolean elimino = eliminarDeVectorOrd(&vec, elemento);
//
//    if(elimino)
//    {
//        printf("OK - elemento %d eliminado. \n", elemento);
//    }
//    else
//    {
//        printf("Error - Debio elimiar el elemento %d, por que existe en el vector. \n", elemento);
//    }

    insertarEnVectorAlFinal(&vec, 6);
    insertarEnVectorAlFinal(&vec, 5);
    insertarEnVectorAlFinal(&vec, 2);
    insertarEnVectorAlFinal(&vec, 9);
    insertarEnVectorAlFinal(&vec, 15);
    insertarEnVectorAlFinal(&vec, 10);
    insertarEnVectorAlFinal(&vec, 1);

    mostrarVector(numeros);
    ordenarGenBurbujeo(numeros, 10);
    mostrarVector(numeros);

//    cantElim = eliminarDeVector(&vec, 15);
//
//    if(cantElim == 0)
//        puts("No se encontro el elemento.\n");
//    else
//        printf("Se eliminaron %d elementos.\n", cantElim);

//    mostrarVector(&vec);

    return 0;
}



void mostrarCodigo(int codigo)
{
    switch(codigo)
    {
    case TODO_OK:
        printf("Elemento insertado");
        break;
    case VEC_LLENO:
        puts("El vector esta lleno. No se pudo insertar.");
        break;
    case DUPLICADO:
        puts("El elemento ya existia. No se pudo insertar.");
        break;
    }
}
