#include <stdio.h>
#include <stdlib.h>
#include "arch.h"



//int crearLote()
//{
//    Proudctos producto[10] = {
//        {"Helado", 10, 10.5},
//        {"Cafe", 10, 10.5},
//        {"Leche", 10, 10.5},
//        {"Pan", 10, 10.5},
//        {"Cereal", 10, 10.5},
//        {"Jugo", 10, 10.5},
//        {"Agua", 10, 10.5},
//        {"Cerveza", 10, 10.5},
//        {"Vino", 10, 10.5},
//        {"Papas", 10, 10.5}
//
//    };
//    FILE* archivo = fopen("arch.dat", "wb");
//    if(archivo == NULL)
//    {
//        printf("No se pudo abrir el archivo");
//        return -1;
//    }
//    fwrite(&producto, sizeof(Proudctos), 10, archivo);
//    fclose(archivo);
//    return 0;
//}


int leerArchTxT()
{
    FILE* archivo = fopen("arch.txt", "rt");
    FILE* archBin = fopen("archDeTxTaBin.dat", "wb");
    if(!archivo)
    {
        printf("No se pudo abrir el archivo TXT");
        return -1;
    }
    if(!archBin)
    {
        printf("No se pudo abrir el archivo BIN");
        return -1;
    }

    Proudctos producto;
    while(fscanf(archivo, "%[^|]|%d|%f \n", producto.codigo, &producto.cantidad, &producto.precio) != EOF)
    {
//        printf("%s %d %.f\n", producto.codigo, producto.cantidad, producto.precio);
        fwrite(&producto, sizeof(Proudctos), 1, archBin);
    }
    fclose(archivo);
    fclose(archBin);
    return 0;
}
