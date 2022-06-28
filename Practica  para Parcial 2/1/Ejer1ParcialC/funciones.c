#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "arbol.h"

int cargarIndice(tArbol* arbol, const char* filename, int(*compararDNI)(const void*, const void*))
{
    int regs = 0;
    tRegInd indice;

    FILE* fp = fopen(filename, "rb");
    if(!fp)
        return 0;

    fread(&indice, sizeof(tRegInd), 1, fp);
    while(!feof(fp))
    {
        insertarEnArbolRec(arbol, &indice, sizeof(tRegInd), compararDNI);
        fread(&indice, sizeof(tRegInd), 1, fp);
    }
    return 1;
}


int compactar_indexar(tArbol* arbol, const char* filename, int(*compararDNI)(const void*, const void*))
{
    int regs = 0;
    tAlumno alumno;
    tRegInd indice;
    FILE* pa = fopen(filename, "rb");
    FILE* pta = fopen("alumnosTemp.dat", "wb");

    if(!pa && !pta)
        return 0;

    fread(&alumno, sizeof(tAlumno), 1, pa);
    while(!feof(pa))
    {
        if(alumno.estado == 'A')
        {
            fwrite(&alumno, sizeof(tAlumno), 1, pta);
            indice.dni = alumno.dni;
            indice.nroReg = regs;
            insertarEnArbolRec(arbol,&indice,sizeof(tRegInd),compararDNI);
        }
        regs++;
        fread(&alumno, sizeof(tAlumno), 1, pa);
    }
    fclose(pa);
    fclose(pta);
    remove(filename);
    rename("alumnosTemp.dat", "alumnos.dat");

    return 1;
}




void rotar90g_inte(tArbol* arbol, void(*accion)(const void*))
{
    if(!*arbol)
        return;

    rotar90Rec(&(*arbol)->der,1,accion);
    accion((*arbol)->info);
    rotar90Rec(&(*arbol)->izq,1,accion);
}



void rotar90Rec(tArbol* arbol,int nivel,void(*accion)(const void*))
{
    if(!*arbol)
        return;

    rotar90Rec(&(*arbol)->der,nivel+1,accion);
    tabRec(nivel,0);
    accion((*arbol)->info);
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


void MostrarArchAlum(const char* filename)
{
    tAlumno alum;
    FILE* pf = fopen(filename, "rb");
    if(!pf)
        return 0;

    fread(&alum, sizeof(tAlumno), 1, pf);
    while(!feof(pf))
    {
        printf("%d, %s, %d, %.2f, %c\n", alum.dni, alum.apyn, alum.cant_materias, alum.promedio, alum.estado);
        fread(&alum, sizeof(tAlumno), 1, pf);
    }
}
