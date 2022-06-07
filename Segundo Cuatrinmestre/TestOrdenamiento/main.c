#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../OrdenamientoGenerico/OrdenamientoGenerico.h"


int cmpInt(const void* a, const void* b);
void mostrarInt(const void* a);
int cmpProductoCodigo(const void* a, const void* b);
int cmpProductoDesc(const void* a, const void* b);
void mostrarProducto(const void* a);


//Estructura Producto
typedef struct
{
    int codigo;
    char descipcion[50];
    int precio;

}Producto;

int main()
{
    // Declarar un vector desordenado de 10 elementos
    int vec[10] = {5, 3, 1, 4, 2, 6, 9, 7, 8, 10};

    //Ordenar el vector con el algoritmo de seleccion
    ordenarGenSeleccion(vec, 10, sizeof(int), cmpInt);
//        ordenarGenBurbujeo(vec, 10);
    puts("vector ordenado con el algoritmo de seleccion");
    mostrarVectorGen(vec, 10, sizeof(int), mostrarInt);

    //Declarar vector de 10 Productos
    Producto productos[10] = {
        {1, "Leche", 2.5},
        {2, "Arroz", 1.5},
        {3, "Huevos", 3.5},
        {4, "Pan", 1.5},
        {5, "Cafe", 2.5},
        {6, "Lavadora", 1500},
        {7, "Televisor", 1500},
        {8, "Celular", 1500},
        {9, "Laptop", 1500},
        {10, "Impresora", 1500}
    };

    ordenarGenSeleccion(productos, 10, sizeof(Producto), cmpProductoDesc);

    puts("Productos ordenados por descripcion");
    mostrarVectorGen(productos, 10, sizeof(Producto), mostrarProducto);


    puts("Productos ordenados por codigo");
    ordenarGenSeleccion(productos, 10, sizeof(Producto), cmpProductoCodigo);
    mostrarVectorGen(productos, 10, sizeof(Producto), mostrarProducto);


    return 0;
}



int cmpInt(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

void mostrarInt(const void* a)
{
    printf("%d ", *(int*)a);
}


int cmpProductoCodigo(const void* a, const void* b)
{
    Producto* prod1 = (Producto*)a;
    Producto* prod2 = (Producto*)b;
    return prod1->codigo - prod2->codigo;
}

int cmpProductoDesc(const void* a, const void* b)
{
    Producto* prod1 = (Producto*)a;
    Producto* prod2 = (Producto*)b;
    return strcmp(prod1->descipcion, prod2->descipcion);
}

void mostrarProducto(const void* a)
{
    Producto* prod = (Producto*)a;
    printf("Codigo: %d\nDescripcion: %s\nPrecio: %d\n", prod->codigo, prod->descipcion, prod->precio);
}
