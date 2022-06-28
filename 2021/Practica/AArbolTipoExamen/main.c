#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "alumnos.h"
#include "../../../Librerias/Arbol.h"
#include "utiles.h"

void guardarRegsIndice(const void* dato, void* contexto);

int compararIndice(const void* a, const void* b);

void mostrarIndice(const void* a);


int main()
{
    int size;
    char op;
    tArbol arbol;
    crearArbol(&arbol);


    const char opciones [][TAM_MENU] = {"coimvabrxyq",
                                    "Crear archivo y cargar indice",
                                    "Cargar indice desde el archivo de datos",
                                    "Cargar indice desde archivo indice",
                                    "Mostrar Arbol",
                                    "Ver caracteristicas",
                                    "Alta",
                                    "Baja",
                                    "Regenerar como arbol balanceado",
                                    "Buscar 1000 en archivo",
                                    "Buscar 1000 en indice",
                                    "Salir"};


    do{
        switch(op){
            case 'C':
                printf("Ingrese el tamanio: ");
                scanf("%d", &size);
                createBigFile(BIGFILENAME, size);
                cargarIndice(&arbol,BIGFILENAME,compararIndice);
                pausa("");
                break;

            case 'O':
                pausa("");
                break;

            case 'I':
                pausa("");
                break;

            case 'M':
                rotar90g_inte(&arbol, mostrarIndice);
                pausa("");
                break;

            case 'V':
                pausa("");
                break;

            case 'R':
                guardarArbolOrdenadoGenerico(&arbol,guardarRegsIndice);
                talarRec(&arbol);
                cargarIndiceArchInOrd(&arbol, compararIndice);
                pausa("");
                break;

            case 'B':
                pausa("");
                break;

            case 'X':
                pausa("");
                break;


            case 'Y':
                pausa("");
                break;


            default:
                fflush(stdin);
                break;
        }
        op = pedir_opcion(opciones, "----Opciones----", "->");


    }while(op!='Q');

    return 0;
}



int compararIndice(const void* a, const void* b)
{
    return ((tidx*)a)->key - ((tidx*)b)->key;
}


void guardarRegsIndice(const void* dato, void* contexto)
{
    fwrite(dato, sizeof(tidx), 1, (FILE*)contexto);
}

void mostrarIndice(const void* a)
{
    printf("%d/%d\n", ((tidx*)a)->key, ((tidx*)a)->position);
}
