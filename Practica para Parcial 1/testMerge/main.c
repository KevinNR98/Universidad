#include <stdio.h>
#include <stdlib.h>

int main()
{
    generarArchivoProducto("Productos.dat");
    generarArchivoMovimientos("Movimientos.dat");

    puts("Archivo Producto antes del Merge:");
    mostrarArchivo("Productos.dat");
    puts("\n");
    puts("Archivo movimientos:");
    mostrarArchivo("Movimientos.dat");

    mergeArch("Productos.dat", "Movimientos.dat");
    puts("\n");
    puts("Archivo Producto despues del Merge:");
    mostrarArchivo("Productos.dat");


    return 0;
}
