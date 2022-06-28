#include <stdio.h>
#include <stdlib.h>
#include "Funciones.h"
#include "Menu.h"

int main()
{
    int dni;
    char op;
    tArbol arbol;
    crearArbol(&arbol);

    const char opciones [][TAM_MENU] = {"COBAMVS",
                                        "Cargar indice desde archivo indice",
                                        "Mostrar Arbol",
                                        "Baja",
                                        "Alta",
                                        "Regenerar como arbol balanceado",
                                        "Mostrar Archivo Alumnos",
                                        "Salir"
                                       };


    do
    {
        switch(op)
        {
        case 'C':
            cargarIndice(&arbol, ARCH_IDX, cmpDni);
            pausa("");
            break;

        case 'O':
            MostrarArbol(&arbol, mostrarIndice);
            pausa("");
            break;

        case 'B':
            puts("Ingrese el DNI del alumno para darlo de BAJA");
            scanf("%d", &dni);
            baja(&arbol, dni, cmpDni);
            pausa("");
            break;

        case 'A':

            pausa("");
            break;


        case 'M':
            vacairArbol(&arbol);
            balancearArbol(&arbol,cmpDni);
            pausa("");
            break;

        case 'V':
            MostrarArchAlum(ARCH_ALUM);
            pausa("");

        default:
            fflush(stdin);
            break;
        }
        op = pedir_opcion(opciones, "----Opciones----", "->");


    }
    while(op!='S');

    return 0;


}
