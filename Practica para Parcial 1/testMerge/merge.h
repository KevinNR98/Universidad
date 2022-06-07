#ifndef MERGE_H_INCLUDED
#define MERGE_H_INCLUDED

#define CANT_PROD_INI   5
#define CANT_MOV_INI    10

typedef struct
{
    char codigo[16];
    char descripcion[51];
    float precioUnitario;
    int cantidad;
}Producto;


int generarArchivoProducto(const char* nombreArch);
int generarArchivoMovimientos(const char* nombreArch);
int mostrarArchivo(const char* nombreArch);
void mostrarProducto(const Producto* producto);
int mergeArch(const char* nomArchProd, const char* nomArchMov);


#endif // MERGE_H_INCLUDED
