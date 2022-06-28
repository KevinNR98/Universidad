#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "menu.h"

void mostrarIndice(const void* a);

void compararDNI(const void*, const void*);

int main()
{
    tArbol indiceArb;
    tAlumno alumno;
    crearArbol(&indiceArb);
    char op;
    const char opciones[][TAM_MENU] = {"CBMRQS",
                                       "Cargar Indice",
                                       "Balancear Arbol",
                                       "Mostrar Arbol",
                                       "Compactar Archivo y Reindexar",
                                       "Mostrar Archivo Alumnos",
                                       "Salir"
                                      };



    do
    {
        switch(op)
        {
        case 'C':
            cargarIndice(&indiceArb, IDXNOMB, compararDNI);
            pausa("");
            break;
        case 'B':

            pausa("");
            break;
        case 'M':
            rotar90g_inte(&indiceArb, mostrarIndice);
            pausa("");
            break;
        case 'R':
//            vaciarArbol(&indiceArb);
//            compactar_indexar(&indiceArb, DATNOM, compararDNI);
            break;
        case 'Q':
            MostrarArchAlum(DATNOM);
            pausa("");
            break;

        default:
            fflush(stdin);
            break;
        }
        op = pedir_opcion(opciones, "----MENU OPCIONES----","->");
    }
    while(op!='S');



    return 0;
}



void mostrarIndice(const void* a)
{
    printf("%d/%d\n", ((tRegInd*)a)->dni, ((tRegInd*)a)->nroReg);
}

void compararDNI(const void* a, const void* b)
{
    return ((tRegInd*)a)->dni - ((tRegInd*)b)->dni;
}

