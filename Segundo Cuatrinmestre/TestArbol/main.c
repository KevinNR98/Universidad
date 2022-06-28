#include <stdio.h>
#include <stdlib.h>

#define TDA_ARBOL_IMPL_DINAMICA
#include "../TDAArbol/TDAArbol.h"

typedef struct 
{
    int dato;
    char descripcion[50];
}Producto;


void grabarProducto(void* producto, void* archivo);


int main()
{
    Arbol arbol;
    crearArbol(&arbol);

    cargarArbol(&arbol);

    FILE* archivo = fopen("arbol.dat", "wb");
    if(!archivo)
    {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    recorrerArbolPrEOrden(&arbol, grabarProducto, archivo);


    fclose(archivo);

    return 0;
}



void grabarProducto(void* producto, void* archivo)
{
    fwrite(producto, sizeof(Producto), 1 , (FILE*)archivo);
}