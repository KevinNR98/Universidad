#include <stdio.h>
#include <stdlib.h>
#include "Funciones.h"
#include "Arbol.h"
#include "ListaDoble.h"



int cargarIndiceArchInOrd(tArbol* arbol, int(*compararIndice)(const void*, const void*))
{
    int tam;
    FILE* fp = fopen(ARCH_COMP_IDX,"rb");
    if(!fp)
        return 0;

    fseek(fp, 0, SEEK_END);
    tam = ftell(fp)/sizeof(tIndComponente);
    tam = cargarIdxArchInOrd_R(arbol, 0, tam-1, fp, compararIndice);

    fclose(fp);
    return tam;
}



int cargarIdxArchInOrd_R(tArbol* arbol, int li, int ls, FILE* arch, int(*compararIndice)(const void*, const void*))
{
    tIndComponente index;
    int pm = li +(ls - li)/2;

    if(li > ls)
    {
        return 1;
    }

    fseek(arch, pm*sizeof(tIndComponente), SEEK_SET);
    fread(&index, sizeof(tIndComponente), 1, arch);
    if(!R_insertarEnArbol(arbol, &index, sizeof(tIndComponente), compararIndice))
    {
        return 0;
    }

    return cargarIdxArchInOrd_R(&(*arbol)->izq, li, pm-1, arch, compararIndice) && cargarIdxArchInOrd_R(&(*arbol)->der, pm+1, ls, arch, compararIndice);
}

int darDeBaja(tArbol* arbol, const char* filename)
{
    int res;
    tIndComponente indx;
    FILE* fp = fopen(filename, "r+b");
    if(!fp)
        return 0;

    inrgresarCod(&indx);
    res = baja(&indx, fp, arbol);
}

int baja(tIndComponente indx, FILE* arch, tArbol* arbol)
{
    tComponente hard;
    unsigned pos;
    unsigned tam;
    if(!buscarClave(arbol, indx.codigo, sizeof(tIndComponente), compararIndice))
    {
        return 0;
    }
    pos = indx.nroReg;
    fseek(arch,0l, SEEK_END);
    tam = (ftell(arch)/ sizeof(tComponente))-1;
    fseek(arch, pos*tam, SEEK_SET);
    fread(&hard, sizeof(tComponente),1,arch);
    printf("", hard.codigo, hard.descripcion, hard.precioUnitario, hard.stock);
}

void inrgresarCod(tIndComponente* indx)
{
    return (indx->codigo) = "HDDSSD1TB";
}


//int alta (t_alumno * alu, FILE * arch, t_arbol* pa)
//{
//    t_reg_ind dato;
//    fseek(arch,0L,SEEK_END);
//    dato.nro_reg=(ftell(arch)/sizeof(t_alumno))-1;
//    dato.dni=alu->dni;
//    if((insertar_en_arbol_bin_busq(pa,&dato,comparacion))!=TODO_OK)
//        return DUPLICADO;
//    fwrite(alu,sizeof(t_alumno),1,arch);
//    return TODO_OK;
//}

//void op_alta(FILE * arch, t_arbol * pindice)
//{
//    int res;
//    t_alumno alu;
//    ingresar_alumno_res(&alu);
//    res= alta_res(&alu, arch, pindice);
//    imprimir_mensaje(res);
//}




tComponente* buscarClave(tArbol* arbol, void* dato, unsigned cantBytes, int(*comparar)(const void*, const void*))
{
    if(!(*arbol))
        return 0;

    if(!(arbol = buscarNodoArbol(arbol,dato,compararIndice)))
        return 0;
    memcpy(dato, (*arbol)->info, MINIMO(cantBytes,(*arbol)->tamInfo));
    return (tComponente*)dato;
}





//void recorrerArbolInOrden(tArbol* arbol, void(*accion)(const void*))///IRD
//{
//    if(!(*arbol))
//    {
//        return;
//    }
//    recorrerArbolInOrden(&(*arbol)->izq,accion);
//    accion((*arbol)->info);
//    recorrerArbolInOrden(&(*arbol)->der,accion);
//}


int cargarArchEnLista(tLista* lista, const char* filename)
{
    tArmadoYRep arm;
    FILE* fp = fopen(filename, "rb");
    if(!fp)
        return 0;

    fread(&arm, sizeof(tArmadoYRep), 1, fp);
    while(!feof(fp))
    {
        if(!insertarEnListaOrdenadoYacum(lista, &arm, sizeof(tArmadoYRep), compararCodigo, acumuladorCantidad))
        {
            return 0;
        }
        fread(&arm, sizeof(tArmadoYRep), 1, fp);
    }
    return 1;
}



////////////////////////////////////////////////////////////////////////////////////////

void mostrarIndiceArch()
{
    tIndComponente indice;
    FILE* fp = fopen(ARCH_COMP_IDX, "rb");
    if(!fp)
        return 0;

    fread(&indice, sizeof(tIndComponente), 1, fp);
    while(!feof(fp))
    {
        printf("%s, %d\n", indice.codigo, indice.nroReg);
        fread(&indice, sizeof(tIndComponente), 1, fp);
    }
}


int compararIndice(const void* a, const void* b)
{
    return ((tIndComponente*)a)->codigo - ((tIndComponente*)b)->codigo;
}

int compararCodigo(const void* a, const void* b)
{

    return ((tArmadoYRep*)a)->codigo - ((tArmadoYRep*)b)->codigo;
//    return *(int*)a - *(int*)b;
}



void mostrarIndice(const void* a)
{
    printf("%s/%d\n", ((tIndComponente*)a)->codigo, ((tIndComponente*)a)->nroReg);
}


int acumuladorCantidad(void** info, unsigned* tam, const void* dato, unsigned cantBytes)
{
    tArmadoYRep **cant1 = (tArmadoYRep**)info;
    tArmadoYRep *cant2 = (tArmadoYRep*)dato;
    (*cant1)->cantidad += cant2->cantidad;
    return 1;
}


void mostrarLista(const void* a)
{
    printf("%d, %s, %d, %.2f\n",((tArmadoYRep*)a)->nroOp, ((tArmadoYRep*)a)->codigo, ((tArmadoYRep*)a)->cantidad, ((tArmadoYRep*)a)->precioUnitario);
}
