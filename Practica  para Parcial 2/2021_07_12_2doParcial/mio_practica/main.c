#include <stdio.h>
#include <stdlib.h>
#include "Funciones.h"
#include "Arbol.h"
#include "ListaDoble.h"

void mostrarComponentes();

int main()
{
    tLista lista;
    tArbol arbol;
    crearArbol(&arbol);
    creaLista(&lista);
    mostrarComponentes();
    puts("\n////////////////////////////////////////////////\n");
    cargarIndiceArchInOrd(&arbol, compararIndice);
//    cargarArchEnLista(&lista, ARCH_AYR_DAT);
//    recorrerListaDer(&lista, mostrarLista);

    puts("\n////////////////////////////////////////////////\n");
    recorrerArbolInOrden(&arbol, mostrarIndice);
    if(esBalanceado(&arbol))
    {
        puts("\nSI\n");
    }
//    leerDesdeArchivoBin(&compo, ARCH_COMP_DAT, 1, sizeof(tComponente));+
    return 0;
}






void mostrarComponentes()
{
    tComponente com;
    FILE* fp = fopen(ARCH_COMP_DAT, "rb");
    if(!fp)
        return 0;

    fread(&com, sizeof(tComponente), 1, fp);
    while(!feof(fp))
    {
        printf("%s, %s, %d, %.2f\n", com.codigo, com.descripcion, com.stock, com.precioUnitario);
        fread(&com, sizeof(tComponente), 1, fp);
    }
}

//mostrarArmadoYre()
//{
//    tArmadoYRep arm;
//    FILE* fp = fopen(ARCH_AYR_DAT, "rb");
//    if(!fp)
//        return 0;
//
//    fread(&arm, sizeof(tArmadoYRep), 1, fp);
//    while(!feof(fp))
//    {
//        printf("%d, %s, %d, %.2f\n", arm.nroOp, arm.codigo, arm.cantidad, arm.precioUnitario);
//        fread(&arm, sizeof(tArmadoYRep), 1, fp);
//    }
//}



