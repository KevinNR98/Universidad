#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Comun/Comun.h"
#include "../Fecha/Fecha.h"

#define TODO_OK 0
#define ERR_ARCHIVO 1
#define ERR_PARAM 2
#define ERR_LINEA_LARGA 3

#define CANT_PROD_INI 5
#define CANT_MOV_INI 10
#define ARG_PORC 2

#define ARG_ARCH_PROD 1
#define ARG_ARCH_MOV 2
#define ARG_ARCH_TXT 3
#define ARG_FORMATO_TXT 4
#define ARG_TXT_A_BIN 5

#define TAM_LINEA 500

typedef struct
{
    char codigo[16];
    char descripcion[51];
    Fecha ultPre;
    float precioUnitario;
    int cantidad;
} Producto;

typedef int (*TxtABin)(char* linea, Producto* producto);


int generarArchivoProducto(const char* nombreArch);
int generarArchivoMovimientos(const char* nombreArch);
int mostrarArchivo(const char* nombreArch);
void mostrarProducto(const Producto* producto);
int actualizarArchivo(const char* nombreArch, float porcentaje);
void actualizarProducto(Producto* producto, float porcentaje);
int merge(const char* nomArchProd, const char* nomArchMov);
int archivoBinATxt(const char* nomArchBin, const char* nomArchTxt, char formatoTxt);
int archivoTxtABin(const char* nomArchTxt, char formatoTxt, const char* nomArchBin);
int archivoTxtABinCValidaciones(const char* nomArchTxt, char formatoTxt, const char* nomArchBin);
int txtVarABin(char* linea, Producto* producto);
int txtFijoABin(char* linea, Producto* producto);

int main(int argc, char* argv[])///le paso por parametros el nombre del archivo que quiero abrir
{
    int ret;
//    float porcentaje;

    if(argc != 6)
    {
        printf("Paso %d parametros, debe pasar 5\n", argc);
        return ERR_PARAM;
    }


    ret = generarArchivoProducto(argv[ARG_ARCH_PROD]);

    if(ret != TODO_OK)
        return ret;
    puts("Antes: ");
    ret = mostrarArchivo(argv[ARG_ARCH_PROD]);///tengo que tener cuidado de andar abriendo y cerrando el archivo por cada cambio que haga, y tratar de abrirlo y cerrarlo lo menos posible
/////////////////////////////////////////////////////////////////
    ret = generarArchivoMovimientos(argv[ARG_ARCH_MOV]);

    if(ret != TODO_OK)
        return ret;
    puts("Movimientos: ");
    ret = mostrarArchivo(argv[ARG_ARCH_MOV]);
    if(ret != TODO_OK)
        return ret;
///////////////////////////////////////////////////////////////
//    porcentaje = atof(argv[ARG_PORC]);///transforma el num que le pase por parametro de un caracter a un nro
//    ret = actualizarArchivo(argv[ARG_MOM_ARCH], porcentaje);
    ret = merge(argv[ARG_ARCH_PROD],argv[ARG_ARCH_MOV]);
    if(ret != TODO_OK)
        return ret;

    puts("Despues: ");
    ret = mostrarArchivo(argv[ARG_ARCH_PROD]);


    ret = archivoBinATxt(argv[ARG_ARCH_PROD], argv[ARG_ARCH_TXT], argv[ARG_FORMATO_TXT][0]);

    puts("Txt a Bin: ");
    ///ret = archivoTxtABin(argv[ARG_ARCH_TXT], argv[ARG_FORMATO_TXT][0], argv[ARG_TXT_A_BIN]);
    ret = archivoTxtABinCValidaciones(argv[ARG_ARCH_TXT], argv[ARG_FORMATO_TXT][0], argv[ARG_TXT_A_BIN]);
    if(ret != TODO_OK)
        return ret;
    ret = mostrarArchivo(argv[ARG_TXT_A_BIN]);
    if(ret != TODO_OK)
        return ret;

    return ret;
}




int generarArchivoProducto(const char* nombreArch)
{
    FILE* arch = fopen(nombreArch, "wb");

    if(!arch)
    {
        printf("El archivo %s no se pudo abrir\n",nombreArch);
        return ERR_ARCHIVO;
    }

    Producto productos[CANT_PROD_INI] =
    {
        {"banana", "Banana",{5, 10, 2021}, 160, 150},
        {"manz", "Manzana",{9, 9, 2021}, 80, 150},
        {"naran", "Naranja",{7, 7, 2021}, 50, 90},
        {"sandia", "Sandia",{8, 8, 2021}, 100, 40},
        {"uva", "Uva",{1, 1, 2021}, 130, 89}
    };

    fwrite(productos,sizeof(Producto), CANT_PROD_INI, arch);

    fclose(arch);

    return TODO_OK;
}

int generarArchivoMovimientos(const char* nombreArch)
{
    FILE* arch = fopen(nombreArch, "wb");

    if(!arch)
    {
        printf("El archivo %s no se pudo abrir\n",nombreArch);
        return ERR_ARCHIVO;
    }

    Producto productos[CANT_MOV_INI] =
    {
        {"banana", "Banana",{8, 10, 2021}, 160, 150},
        {"kiwi", "Kiwi",{1, 1, 2021}, 200, 30},
        {"mango", "Mango",{2, 2, 2021}, 100, 30},
        {"mango", "Mango",{3, 10, 2021}, 105, 50},
        {"manz", "Manzana",{4, 1, 2021}, 80, 150},
        {"naran", "Naranja",{5, 2, 2021}, 50, 90},
        {"naran", "Naranja",{6, 3, 2021}, 55, 30},
        {"pera", "Pera",{7, 4, 2021}, 60, 100},
        {"pome", "Pomelo",{8, 5, 2021}, 140, 20},
        {"sandia", "Sandia",{9, 6, 2021}, 100, 40}
    };

    fwrite(productos,sizeof(Producto), CANT_MOV_INI, arch);

    fclose(arch);

    return TODO_OK;
}


int mostrarArchivo(const char* nombreArch)
{
    FILE* arch = fopen(nombreArch, "rb");
    Producto producto;

    if(!arch)
    {
        printf("El archivo %s no se pudo abrir\n",nombreArch);
        return ERR_ARCHIVO;
    }

    fread(&producto, sizeof(Producto), 1, arch);
    while(!feof(arch))
    {
        mostrarProducto(&producto);
        fread(&producto, sizeof(Producto), 1, arch);
    }


    fclose(arch);

    return TODO_OK;
}


void mostrarProducto(const Producto* producto)
{
    printf("[Codigo: %s, Descr: %s,UltPre: %d/%d/%d , PreUni $%.2f, Cant: %d]\n",
           producto->codigo, producto->descripcion, producto->ultPre.dia,
           producto->ultPre.mes, producto->ultPre.anio,producto->precioUnitario, producto->cantidad);
}


int actualizarArchivo(const char* nombreArch, float porcentaje)
{
    FILE* arch = fopen(nombreArch, "r+b");
    Producto producto;

    if(!arch)
    {
        printf("El archivo %s no se pudo abrir\n",nombreArch);
        return ERR_ARCHIVO;
    }

    fread(&producto, sizeof(Producto), 1, arch);
    while(!feof(arch))
    {
        actualizarProducto(&producto, porcentaje);///modifico el dato
        fseek(arch, -(long)sizeof(Producto), SEEK_CUR);///tengo que colocarme en el dato que voy a modificar, por que el puntero de lectura se posiciono en el sig dato
        fwrite(&producto, sizeof(Producto), 1, arch);///escribo lo que acabo de modificar
        fseek(arch, 0, SEEK_CUR);/// si no hago esto no puedo leer el siguiente dato
        fread(&producto, sizeof(Producto), 1, arch);
    }


    fclose(arch);
    return TODO_OK;
}


void actualizarProducto(Producto* producto, float porcentaje)
{
    producto->precioUnitario *= 1 + porcentaje / 100;
}



int merge(const char* nomArchProd, const char* nomArchMov)
{
    int comp;
    Producto prod,prodNue, mov;
    FILE* archProd = fopen(nomArchProd, "rb");

    if(!archProd)
    {
        printf("El archivo %s no se pudo abrir\n",nomArchProd);
        return ERR_ARCHIVO;
    }

    FILE* archMov = fopen(nomArchMov, "rb");

    if(!archMov)
    {
        printf("El archivo %s no se pudo abrir\n",nomArchMov);
        return ERR_ARCHIVO;
    }

    FILE* archProdTmp = fopen("Productos.Tmp", "wb");

    if(!archProdTmp)
    {
        printf("El archivo temporal no se pudo abrir\n");
        return ERR_ARCHIVO;
    }

    fread(&prod, sizeof(Producto), 1, archProd);
    fread(&mov, sizeof(Producto), 1, archMov);
    while(!feof(archProd) && !feof(archMov))
    {
        comp = strcmp(prod.codigo, mov.codigo);

        if(comp == 0)
        {
            prod.cantidad += mov.cantidad;
            prod.precioUnitario = mov.precioUnitario;
            fread(&mov, sizeof(Producto), 1, archMov);///leo otra vez por si hay otro prod igual, por eso espero para escribir el arch temp
        }

        if(comp < 0)
        {
            fwrite(&prod, sizeof(Producto), 1, archProdTmp);/// ahora si lo grabo por que ya no hay mas prod iguales
            fread(&prod, sizeof(Producto), 1, archProd);
        }

        if(comp > 0)
        {
            prodNue = mov; ///copio para despues poder ir act el prod si hay prod iguales y el archProd termino o no avanza
            fread(&mov, sizeof(Producto), 1, archMov);
            while(!feof(archMov) && strcmp(mov.codigo, prodNue.codigo) == 0)
            {
                prodNue.cantidad += mov.cantidad;
                prodNue.precioUnitario = mov.precioUnitario;
                fread(&mov, sizeof(Producto), 1, archMov);
            }
            fwrite(&prodNue, sizeof(Producto), 1, archProdTmp);
        }
    }


    while(!feof(archProd))///compruebo si termino de leer el arch, y si no copio lo que queda
    {
        fwrite(&prod, sizeof(Producto), 1, archProdTmp);
        fread(&prod, sizeof(Producto), 1, archProd);
    }

    while(!feof(archMov))
    {
        prodNue = mov;

        fread(&mov, sizeof(Producto), 1, archMov);
        while(!feof(archMov) && strcmp(mov.codigo, prodNue.codigo) == 0)
        {
            prodNue.cantidad += mov.cantidad;
            prodNue.precioUnitario = mov.precioUnitario;
            fread(&mov, sizeof(Producto), 1, archMov);
        }
        fwrite(&prodNue, sizeof(Producto), 1, archProdTmp);
    }

    fclose(archProd);
    fclose(archMov);
    fclose(archProdTmp);
    remove(nomArchProd);///primero tengo que cerrar el archivo si no, no me lo va a dejar eliminar
    rename("Productos.tmp", nomArchProd);

    return TODO_OK;
}


int archivoBinATxt(const char* nomArchBin, const char* nomArchTxt, char formatoTxt)
{
    char* formatoFprintf = formatoTxt == 'V'?"%s|%s|%d/%d/%d|%.2f|%d\n": "%-15s%-50s%02d/%02d/%04d%07.2f%03d\n";
    Producto producto;
    FILE* archBin = fopen(nomArchBin, "rb");

    if(!archBin)
    {
        printf("El archivo %s no se pudo abrir\n",nomArchBin);
        return ERR_ARCHIVO;
    }


    FILE* archTxt = fopen(nomArchTxt, "wt");

    if(!archTxt)
    {
        printf("El archivo %s no se pudo abrir\n", nomArchTxt);
        return ERR_ARCHIVO;
    }

    fread(&producto, sizeof(Producto), 1, archBin);
    while(!feof(archBin))
    {
        fprintf(archTxt, formatoFprintf,
                producto.codigo, producto.descripcion, producto.ultPre.dia, producto.ultPre.mes,
                producto.ultPre.anio,producto.precioUnitario, producto.cantidad); ///parceo el archivo de forma directa dependiendo de si es Variable o Fijo
        fread(&producto, sizeof(Producto), 1, archBin);
    }

    fclose(archBin);
    fclose(archTxt);

    return TODO_OK;
}




int archivoTxtABin(const char* nomArchTxt, char formatoTxt, const char* nomArchBin)
{
    char* formatoFscanf = formatoTxt == 'V'?"%[^|]|%[^|]|%d/%d/%d|%f|%d\n" : "%15s%50s%2d/%2d/%4d%7f%3d\n";///[^|] lee hasta uno antes de pipe, no hace falta poner los decimales (si lo hago se rompe), solo tengo que poner lo que ocupa el campo por que solo lo estoy leyendo
    Producto producto;
    FILE* archBin = fopen(nomArchBin, "wb");
    if(!archBin)
    {
        printf("El archivo %s no se pudo abrir\n", nomArchBin);
        return ERR_ARCHIVO;
    }

    FILE* archTxt = fopen(nomArchTxt, "rt");
    if(!archTxt)
    {
        printf("El archivo %s no se pudo abrir\n", nomArchTxt);
        return ERR_ARCHIVO;
    }

    while(fscanf(archTxt, formatoFscanf,
                 producto.codigo, producto.descripcion, &producto.ultPre.dia, &producto.ultPre.mes,
                 &producto.ultPre.anio,&producto.precioUnitario, &producto.cantidad) != EOF) //// mientras no sea fin de archivo, con fscanf no puedo validad los campos para eso deberia utiliza scanf
    {
        fwrite(&producto, sizeof(Producto), 1, archBin);
    }

    fclose(archBin);
    fclose(archTxt);

    return TODO_OK;
}


int archivoTxtABinCValidaciones(const char* nomArchTxt, char formatoTxt, const char* nomArchBin)///para ancho variable
{
    char linea[TAM_LINEA];
    boolean errorFatal = falso;
    int codigoRetorno = TODO_OK;

    ///char* formatoFscanf = formatoTxt == 'V'?"%[^|]|%[^|]|%d/%d/%d|%f|%d\n" : "%15s%50s%2d/%2d/%4d%7f%3d\n";///[^|] lee hasta uno antes de pipe, no hace falta poner los decimales (si lo hago se rompe), solo tengo que poner lo que ocupa el campo por que solo lo estoy leyendo
    Producto producto;
    FILE* archBin = fopen(nomArchBin, "wb");
    if(!archBin)
    {
        printf("El archivo %s no se pudo abrir\n", nomArchBin);
        return ERR_ARCHIVO;
    }

    FILE* archTxt = fopen(nomArchTxt, "rt");
    if(!archTxt)
    {
        printf("El archivo %s no se pudo abrir\n", nomArchTxt);
        return ERR_ARCHIVO;
    }

    TxtABin txtABin = formatoTxt == 'V'? txtVarABin: txtFijoABin;

    while(!errorFatal && fgets(linea, TAM_LINEA, archTxt))
    {
        codigoRetorno = txtABin(linea, &producto);

///        errorFatal = determinarSiEsErrorFatal(codigoRetorno);


        if(codigoRetorno == TODO_OK)
            fwrite(&producto, sizeof(Producto), 1, archBin);
    }

    fclose(archBin);
    fclose(archTxt);

    return codigoRetorno;
}




int txtVarABin(char* linea, Producto* producto)
{
    char* act;
    int codigoRetorno = TODO_OK;
    act = strchr(linea, '\n');
    if(!act)
        codigoRetorno = ERR_LINEA_LARGA;

    if(codigoRetorno == TODO_OK)
    {
        ///Cantidad
        *act = '\0'; ///pone le \0 donde esta el \n
        act = strrchr(linea,'|');
        ///codigoRetorno = validadTextoEntero(act + 1)///TODO : validar el campo a nivel texto
        sscanf(act + 1, "%d", &producto->cantidad);
    }

    if(codigoRetorno == TODO_OK)
    {
        ///Precio Unitario
        *act = '\0';
        act = strrchr(linea,'|');
        ///codigoRetorno = validadTextoDecimal(act + 1)///TODO : validar el campo a nivel texto
        sscanf(act + 1, "%f", &producto->precioUnitario);
    }

    if(codigoRetorno == TODO_OK)
    {
        ///Fecha ult precio
        *act = '\0';
        act = strrchr(linea,'|');
        ///codigoRetorno = validadTextoFecha(act + 1)///TODO : validar el campo a nivel texto
        sscanf(act + 1, "%d/%d/%d", &producto->ultPre.dia, &producto->ultPre.mes, &producto->ultPre.anio);///despued de convertirlo a vinario lo tendria que validar con fecha valida
    }



    if(codigoRetorno == TODO_OK)
    {
        ///Descripcion
        *act = '\0';
        act = strrchr(linea,'|');
        ///codigoRetorno = normalizarTextoDescripcion(act + 1)///TODO : validar el campo a nivel texto
        strncpy(producto->descripcion, act + 1, 51);
    }


    if(codigoRetorno == TODO_OK)
    {
        ///Codigo
        *act = '\0';
        ///codigoRetorno = normalizarTextoCodigo(act + 1)///TODO : validar el campo a nivel texto
        strcpy(producto->codigo, linea);
    }
    return codigoRetorno;
}





int txtFijoABin(char* linea, Producto* producto)
{
    char* act;
    int codigoRetorno = TODO_OK;
    act = strchr(linea, '\n');
    if(!act)
        codigoRetorno = ERR_LINEA_LARGA;

    if(codigoRetorno == TODO_OK)
    {
        ///Cantidad
        *act = '\0'; ///pone le \0 donde esta el \n
        act -= 3;
        ///codigoRetorno = validadTextoEntero(act + 1)///TODO : validar el campo a nivel texto
        sscanf(act, "%d", &producto->cantidad);
    }

    if(codigoRetorno == TODO_OK)
    {
        ///Precio Unitario
        *act = '\0';
        act -= 7;
        ///codigoRetorno = validadTextoDecimal(act + 1)///TODO : validar el campo a nivel texto
        sscanf(act, "%f", &producto->precioUnitario);
    }

    if(codigoRetorno == TODO_OK)
    {
        ///Fecha ult precio
        *act = '\0';
        act -= 8;
        ///codigoRetorno = validadTextoFecha(act + 1)///TODO : validar el campo a nivel texto
        sscanf(act, "%2d/%2d/%4d", &producto->ultPre.dia, &producto->ultPre.mes, &producto->ultPre.anio);///despued de convertirlo a vinario lo tendria que validar con fecha valida
    }



    if(codigoRetorno == TODO_OK)
    {
        ///Descripcion
        *act = '\0';
        act -= 51;
        ///codigoRetorno = normalizarTextoDescripcion(act + 1)///TODO : validar el campo a nivel texto
        ///TODO: llamar a trim() para sacar los espacios de relleno.
        strcpy(producto->descripcion, act);
    }

    if(codigoRetorno == TODO_OK)
    {
        ///Codigo
        *act = '\0';
        ///codigoRetorno = normalizarTextoCodigo(act + 1)///TODO : validar el campo a nivel texto
        ///TODO: llamar a trim() para sacar los espacios de relleno.
        strcpy(producto->codigo, linea);
    }
    return codigoRetorno;
}
