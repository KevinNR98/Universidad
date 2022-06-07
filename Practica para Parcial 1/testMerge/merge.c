#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "merge.h"


int generarArchivoProducto(const char* nombreArch)
{
    FILE* arch = fopen(nombreArch, "wb");

    if(!arch)
    {
        printf("El archivo %s no se pudo abrir\n",nombreArch);
        return 1;
    }

    Producto productos[CANT_PROD_INI] =
    {
        {"banana", "Banana", 160, 150},
        {"manz", "Manzana", 80, 150},
        {"naran", "Naranja", 50, 90},
        {"sandia", "Sandia", 100, 40},
        {"uva", "Uva", 130, 89}
    };

    fwrite(productos,sizeof(Producto), CANT_PROD_INI, arch);

    fclose(arch);

    return 0;
}

int generarArchivoMovimientos(const char* nombreArch)
{
    FILE* arch = fopen(nombreArch, "wb");

    if(!arch)
    {
        printf("El archivo %s no se pudo abrir\n",nombreArch);
        return 1;
    }

    Producto productos[CANT_MOV_INI] =
    {
        {"banana", "Banana", 160, 150},
        {"kiwi", "Kiwi", 200, 30},
        {"mango", "Mango", 100, 30},
        {"mango", "Mango", 105, 50},
        {"manz", "Manzana", 80, 150},
        {"naran", "Naranja", 50, 90},
        {"naran", "Naranja", 55, 30},
        {"pera", "Pera", 60, 100},
        {"pome", "Pomelo", 140, 20},
        {"sandia", "Sandia", 100, 40}
    };

    fwrite(productos,sizeof(Producto), CANT_MOV_INI, arch);

    fclose(arch);

    return 0;
}


int mergeArch(const char* nomArchProd, const char* nomArchMov)
{
    int cmp;
    Producto prod, prodNue, prodMov;

    FILE* archProd = fopen(nomArchProd, "rb");
    if(!archProd)
        return 1;

    FILE* archMov = fopen(nomArchMov, "rb");
    if(!archMov)
        return 1;

    FILE* archProdTemp = fopen("arcProdTemp.tmp", "wb");
    if(!archProdTemp)
        return 1;




    fread(&prod, sizeof(Producto), 1, archProd);
    fread(&prodMov, sizeof(Producto), 1, archMov);
    while(!feof(archProd) && !feof(archMov))
    {
        cmp = strcmp(prod.codigo, prodMov.codigo);

        if(cmp == 0)
        {
            prod.cantidad += prodMov.cantidad;
            prod.precioUnitario = prodMov.precioUnitario;
            fread(&prodMov, sizeof(Producto), 1, archMov);
        }

        if(cmp < 0)
        {
            fwrite(&prod, sizeof(Producto), 1, archProdTemp);
            fread(&prod, sizeof(Producto), 1, archProd);
        }

        if(cmp > 0)
        {
            prodNue = prodMov;
            fread(&prodMov, sizeof(Producto), 1, archMov);
            while(!feof(archMov) && strcmp(prodNue.codigo, prodMov.codigo) == 0)
            {
                prodNue.cantidad += prodMov.cantidad;
                prodNue.precioUnitario = prodMov.precioUnitario;
                fread(&prodMov, sizeof(Producto), 1, archMov);
            }
            fwrite(&prodNue, sizeof(Producto), 1, archProdTemp);
        }
    }

    while(!feof(archProd))
    {
        fwrite(&prod, sizeof(Producto), 1, archProdTemp);
        fread(&prod, sizeof(Producto), 1, archProd);
    }

    while(!feof(archMov))
    {
        prodNue = prodMov;
        fread(&prodMov, sizeof(Producto), 1, archMov);
        while(!feof(archMov) && strcmp(prodNue.codigo, prodMov.codigo) == 0)
        {
            prodNue.cantidad += prodMov.cantidad;
            prodNue.precioUnitario = prodMov.precioUnitario;
            fread(&prodMov, sizeof(Producto), 1, archMov);
        }
        fwrite(&prodNue, sizeof(Producto), 1, archProdTemp);
    }




    fclose(archProd);
    fclose(archMov);
    fclose(archProdTemp);
    remove(nomArchProd);
    rename("arcProdTemp.tmp", nomArchProd);

    return 1;
}





int mostrarArchivo(const char* nombreArch)
{
    FILE* arch = fopen(nombreArch, "rb");
    Producto producto;

    if(!arch)
    {
        printf("El archivo %s no se pudo abrir\n",nombreArch);
        return 1;
    }

    fread(&producto, sizeof(Producto), 1, arch);
    while(!feof(arch))
    {
        mostrarProducto(&producto);
        fread(&producto, sizeof(Producto), 1, arch);
    }


    fclose(arch);

    return 0;
}


void mostrarProducto(const Producto* producto)
{
    printf("[Codigo: %s, Descr: %s, PreUni $%.2f, Cant: %d]\n",
           producto->codigo, producto->descripcion, producto->precioUnitario, producto->cantidad);
}
