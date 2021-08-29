#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"
#include "funres.h"

///#define PANTALLA
///#define ESALUMNO

#ifdef ESALUMNO
#define NOM_ARCH_LPRUEBA "loteprueba.txt"
#else
//#define NOM_ARCH_LPRUEBA "lotepruebadefault.txt"
#define NOM_ARCH_LPRUEBA "loteprueba.txt"
#endif
#include "miFuncion.h"


#ifdef PANTALLA
#define NOM_ARCH_SALIDA "\0"
#else
#define NOM_ARCH_SALIDA "informe.txt"
#endif // PANTALLA

int main()
{

    //Sectores y muelles
    const tsector secs[] = {{'A', 3},{'B', 2},{'C',4},{'D',5}};

//    if (!crearLotePrueba_res(NOM_ARCH_LPRUEBA)){
//        puts("Error al crear lote de prueba\n");
//        return 1;
//    }


    if (!crearLotePrueba_mio(NOM_ARCH_LPRUEBA))
    {
        puts("Error al crear lote de prueba\n");
        return 1;
    }

        if(!generarInforme_mio(NOM_ARCH_LPRUEBA, NOM_ARCH_SALIDA, secs))
    {
        puts("No se pudo abrir el archivo de entradas y salidas\n");
        return 1;
    }



//    if(!generarInforme_res(NOM_ARCH_LPRUEBA, NOM_ARCH_SALIDA, secs))
//    {
//        puts("No se pudo abrir el archivo de entradas y salidas\n");
//        return 1;
//    }



    printf("Fin de ejecucion\n");
    return 0;
}
