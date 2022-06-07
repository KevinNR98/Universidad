#include <stdio.h>
#include <stdlib.h>
#include "arch.h"

int main()
{
//    crearLote();
//
//    Proudctos producto;
//    FILE* arch = fopen("arch.dat", "rb");
//    if(!arch)
//    {
//        printf("No se pudo abrir el archivo BIN");
//        return -1;
//    }
//    FILE* archTxt = fopen("arch.txt", "wt");
//    if(!archTxt)
//    {
//        printf("No se pudo abrir el archivo TXT");
//        return -1;
//    }
//
//
//    fread(&producto, sizeof(Proudctos), 1, arch);
//    while(!feof(arch))
//    {
//        fprintf(archTxt, "%s|%d|%f\n", producto.codigo, producto.cantidad, producto.precio);
//        fread(&producto, sizeof(Proudctos), 1, arch);
//    }

    leerArchTxT();

    FILE* archBin = fopen("archDeTxTaBin.dat", "rb");
    if(!archBin)
    {
        printf("No se pudo abrir el archivo BIN");
        return -1;
    }
    Proudctos producto2;
    fread(&producto2, sizeof(Proudctos), 1, archBin);
    while(!feof(archBin))
    {
        printf("%s|%d|%f\n", producto2.codigo, producto2.cantidad, producto2.precio);
        fread(&producto2, sizeof(Proudctos), 1, archBin);
    }

    return 0;
}
