#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

int main()
{
    FILE* pStockA;
    FILE* pStockB;
    FILE* pNovedad;
    FILE* pMaestro;
    FILE* pMaestro1;

    tProducto S_Maestro;

    char destino[] = "";
    const char origen[]  = "hola juan";
    //////////////////////////////////////PUNTO 1///////////////////////////////////////////////////////////
//    printf("Antes memmove dest = %s, src = %s\n", destino, origen);
//    memmove(destino, origen, strlen(origen)+1);
//    printf("Despues memmove dest = %s, src = %s\n", destino, origen);

    printf("Antes memmove: dest = %s, orig = %s\n", destino, origen);
    mi_Memmove(destino, origen, strlen(origen)+1);
    printf("Despues memmove: dest = %s, orig = %s\n", destino, origen);
    //////////////////////////////////////PUNTO 2///////////////////////////////////////////////////////////
    loteDePrueba();

    pStockA = fopen("StockA.bin","rb");
    if(!pStockA)
    {
        printf("ERROR al abrir el archivo StockA.bin");
        return -1;
    }

    pStockB = fopen("StockB.txt","rt");
    if(!pStockB)
    {
        printf("ERROR al abrir el archivo StockB.txt");
        return -2;
    }

    pMaestro = fopen("Maestro.bin","rb");
    if(!pMaestro)
    {
        printf("ERROR al abrir el archivo Maestro.bin");
        return -9;
    }
    fusionarArch(pStockA, pStockB);
    ///printf("id:%lu des:%s fecha:%d/%d/%d cant: %d  precio: %f\n", S_stockB.idProducto, S_stockB.descripcion, S_stockB.fecUltAct.dia,S_stockB.fecUltAct.mes,S_stockB.fecUltAct.anio, S_stockB.cantidad,S_stockB.precioUnitario);

//    fread(&S_Maestro, sizeof(tProducto),1,pMaestro);
//    while(!feof(pMaestro))
//    {
//        printf("id:%lu des:%s fecha:%d/%d/%d cant: %d  precio: %f\n",S_Maestro.idProducto, S_Maestro.descripcion, S_Maestro.fecUltAct.dia,S_Maestro.fecUltAct.mes,S_Maestro.fecUltAct.anio, S_Maestro.cantidad,S_Maestro.precioUnitario);
//        fread(&S_Maestro, sizeof(tProducto),1,pMaestro);
//    }
    //////////////////////////////////////PUNTO 3///////////////////////////////////////////////////////////
    eliminarDuplicados(pMaestro);
    fclose(pMaestro);

    pMaestro1 = fopen("Maestro1.bin","r+b");
    if(!pMaestro1)
    {   printf("ERROR al abrir el archivo Maestro1.bin");
        return -1;
    }
//    fread(&S_Maestro, sizeof(tProducto),1,pMaestro1);
//    while(!feof(pMaestro1))
//    {
//        printf("id:%lu des:%s fecha:%d/%d/%d cant: %d  precio: %f\n",S_Maestro.idProducto, S_Maestro.descripcion, S_Maestro.fecUltAct.dia,S_Maestro.fecUltAct.mes,S_Maestro.fecUltAct.anio, S_Maestro.cantidad,S_Maestro.precioUnitario);
//        fread(&S_Maestro, sizeof(tProducto),1,pMaestro1);
//    }
    //////////////////////////////////////PUNTO 5///////////////////////////////////////////////////////////
    pNovedad = fopen("novedades.bin","rb");
    if(!pNovedad)
    {
        printf("ERROR al abrir el archivo novedades.bin");
        return -1;
    }
    actualizarArch(pMaestro1, pNovedad);
    rewind(pMaestro1);
    fread(&S_Maestro, sizeof(tProducto),1,pMaestro1);
    printf("ID  PRODUCTO                       FECHA   CANT  PRECIO \n");
    while(!feof(pMaestro1))
    {
        printf("%lu  %-26s  %2d/%2d/%2d  %3d  %.2f\n",S_Maestro.idProducto, S_Maestro.descripcion, S_Maestro.fecUltAct.dia,S_Maestro.fecUltAct.mes,S_Maestro.fecUltAct.anio, S_Maestro.cantidad,S_Maestro.precioUnitario);
        fread(&S_Maestro, sizeof(tProducto),1,pMaestro1);
    }

    fclose(pMaestro1);
    return 0;
}
