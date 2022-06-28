#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"
#include "alumnos.h"
#include "../../../Librerias/Arbol.h"



int cargarIndice(tArbol* arbol, const char* filename, int(*comparar)(const void*, const void*))
{
    int regs = 0;
    tdat alumno;
    tidx tIndice;

    FILE* fp = fopen(filename, "rb");

    if(!fp)
        return 0;

    fread(&alumno, sizeof(tdat), 1, fp);
    while(!feof(fp))
    {

        tIndice.key = alumno.key;
        tIndice.position = regs;
        R_insertarEnArbol(arbol, &tIndice, sizeof(tidx), comparar);///controlar  que se pudo insertar duplicados o pudo reservar memoria
        regs++;
        fread(&alumno, sizeof(tdat), 1, fp);
    }
    return 1;
}


int cargarIndiceArchInOrd(tArbol* arbol, int(*comparar)(const void*, const void*))
{
    int tam;
    FILE* fp = fopen("temp.idx","rb");
    if(!fp)
        return 0;

    fseek(fp, 0, SEEK_END);
    tam = ftell(fp)/sizeof(tidx);
    tam = cargarIdxArchInOrd_R(arbol, 0, tam-1, fp, comparar);

    fclose(fp);
    unlink("temp.idx");
    return tam;
}



int cargarIdxArchInOrd_R(tArbol* arbol, int li, int ls, FILE* arch, int(*comparar)(const void*, const void*))
{
    tidx index;
    int pm = li +(ls - li)/2;

    if(li > ls)
    {
    return 1;
    }

    fseek(arch, pm*sizeof(tidx), SEEK_SET);
    fread(&index, sizeof(tidx), 1, arch);
    if(!R_insertarEnArbol(arbol, &index, sizeof(tidx), comparar))
    {
        return 0;
    }

    return cargarIdxArchInOrd_R(&(*arbol)->izq, li, pm-1, arch, comparar) && cargarIdxArchInOrd_R(&(*arbol)->der, pm+1, ls, arch, comparar);
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////funciones DEL ARBOL

int guardarArbolOrdenadoGenerico(tArbol* arbol, void(*accion)(const void* dato, const void* contexto))///En un arch TEMP
{
    FILE* temp = fopen("temp.idx","wb");
    if(!temp)
        return 0;


    inOrderArchivos(arbol, accion, temp);
    fclose(temp);
    return 1;
}


void inOrderArchivos(tArbol* arbol, void(*accion)(const void* dato, const void* contexto), void* parametros)
{
    if(!(*arbol))
        return;

    inOrderArchivos(&(*arbol)->izq, accion, parametros);
    accion((*arbol)->info, parametros);
    inOrderArchivos(&(*arbol)->der, accion, parametros);
}




///Mostrar arbol de costado (wrapper)
void rotar90g_inte(tArbol* arbol, void(*accion)(const void*))
{
    if(!*arbol)
        return;
// rotar90Rec(arbol,0,accion);
    rotar90Rec(&(*arbol)->der,1,accion);
    accion((*arbol)->info);
    rotar90Rec(&(*arbol)->izq,1,accion);
}
///(la que es recursiva)

void rotar90Rec(tArbol* arbol,int nivel,void(*accion)(const void*))
{
    if(!*arbol)
        return;

///printf("t");
    rotar90Rec(&(*arbol)->der,nivel+1,accion);
    tabRec(nivel,0);
///printf("t");
    accion((*arbol)->info);
///printf("t");
    rotar90Rec(&(*arbol)->izq,nivel+1,accion);
}

void tabRec(int nivel,int cont)
{
    if((nivel)>cont)
    {
        printf("\t");
        tabRec(nivel,cont+1);
    }
    return;
}



///vacia el arbol
///(la llama el main)
void talar (tArbol * arbol)
{
    talarRec (arbol);

}
///complementa a talar y a su vez a talarXNivel
void talarRec (tArbol * arbol)
{
    if(!*arbol)
        return;

    talarRec (&(*arbol)->izq);
    talarRec (&(*arbol)->der);

    free((*arbol)->info);
    free((*arbol));
    *arbol = NULL;
}

