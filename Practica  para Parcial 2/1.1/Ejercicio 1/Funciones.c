#include <stdio.h>
#include "Funciones.h"
#include "Arbol.h"

int cargarIndice(tArbol* arbol, const char* filename, int(*cmpDni)(const void*, const void*))
{
    tRegInd indice;

    FILE* fp = fopen(filename, "rb");
    if(!fp)
        return 0;

    fread(&indice, sizeof(tRegInd), 1, fp);
    while(!feof(fp))
    {
        insertarEnArbolRec(arbol, &indice, sizeof(tRegInd), cmpDni);
        fread(&indice, sizeof(tRegInd), 1, fp);
    }
    return 1;
}


int balancearArbol(tArbol* arbol, int(*cmpDni)(const void*, const void*))
{
    int tam;
    FILE* fp = fopen(ARCH_IDX, "rb");
    if(!fp)
        return 0;

    fseek(fp, 0, SEEK_END);
    tam = ftell(fp)/sizeof(tRegInd);
    tam = balancearArbolRec(arbol, 0, tam-1, fp, cmpDni);

    fclose(fp);
    return tam;
}


int balancearArbolRec(tArbol* arbol, int li, int ls, FILE* arch, int(*cmpDni)(const void*, const void*))
{
    tRegInd indice;
    int pm = (li + ls)/2;

    if(li > ls)
    {
        return 1;
    }

    fseek(arch, pm*sizeof(tRegInd), SEEK_SET);
    fread(&indice, sizeof(tRegInd), 1, arch);
    if(!insertarEnArbolRec(arbol, &indice, sizeof(tRegInd),cmpDni))
    {
        return 0;
    }

    return balancearArbolRec(&(*arbol)->izq, li, pm-1, arch, cmpDni) && balancearArbolRec(&(*arbol)->der, pm+1, ls, arch, cmpDni);
}

void ingresarDniAlumn(tAlumno* alumno)
{

}



int baja(tArbol* arbol, int dni, int(*cmpDni)(const void*, const void*))
{
    int cmp;
    tRegInd indice;
    tAlumno alumno;

    if(!(arbol = buscarNodoArbol(arbol, (void*)dni, cmpDni)))
        return 0;
    memcpy(&indice, (*arbol)->info, sizeof(tRegInd));


    return 1;
}









void MostrarArbol(tArbol* arbol, void(*accion)(const void*))
{
    if(!*arbol)
        return;

    rotar90g(&(*arbol)->der,1,accion);
    accion((*arbol)->info);
    rotar90g(&(*arbol)->izq,1,accion);

}


void rotar90g(tArbol* arbol, int nivel, void(*accion)(const void*))
{
    if(!*arbol)
        return;

    rotar90g(&(*arbol)->der, nivel+1, accion);
    ponerTab(nivel, 0);
    accion((*arbol)->info);
    rotar90g(&(*arbol)->izq, nivel+1, accion);
}


void ponerTab(int nivel, int cont)
{
    if((nivel)>cont)
    {
        printf("\t");
        ponerTab(nivel,cont+1);
    }
    return;
}


void MostrarArchAlum(const char* filename)
{
    tAlumno alum;
    FILE* pf = fopen("alumnos.dat","rb");
    if(!pf)
        return 0;

    fread(&alum, sizeof(tAlumno), 1, pf);
    while(!feof(pf))
    {
        printf("%d, %s, %d, %f, %c\n", alum.dni, alum.apyn, alum.cant_materias, alum.promedio, alum.estado);
        fread(&alum, sizeof(tAlumno), 1, pf);
    }
}

int cmpDni(const void* a, const void* b)
{
    return ((tAlumno*)a)->dni - ((tAlumno*)b)->dni;
}


void mostrarIndice(const void* a)
{
    printf("%d/%d\n", ((tRegInd*)a)->dni, ((tRegInd*)a)->nro_reg);
}
