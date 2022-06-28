#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ArbolBinario.h"

/// si quiero guardar el arbol tal como fue creado debo recorrerlo en preOrden para guardarlo.

void crearArbol(tArbol* arbol)
{
    *arbol = NULL;
}


int R_insertarEnArbol(tArbol* arbol, void* dato, unsigned cantBytes, int(*comparar)(const void*, const void*))
{
    tNodoArbol* nue;
    int cmp;

    if(*arbol)
    {
        if((cmp = comparar((*arbol)->info, dato)) > 0)
        {
            return R_insertarEnArbol(&(*arbol)->izq, dato, cantBytes, comparar);
        }
        else if(cmp < 0)
        {
            return R_insertarEnArbol(&(*arbol)->der, dato, cantBytes, comparar);
        }
        else
        {
            return 2;
        }
    }

    nue = (tNodoArbol*)malloc(sizeof(tNodoArbol));
    if(!nue)
        return 0;
    nue->info = malloc(cantBytes);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, dato, cantBytes);
    nue->tamInfo = cantBytes;
    nue->izq = NULL;
    nue->der = NULL;
    *arbol = nue;

    return 1;
}

//int R_insertarEnArbolOrdenado(tArbol* arbol, void* dato, unsigned cantBytes, int(*comparar)(const void*, const void*))
//{
//
//}

void recorrerArbolPreOrden(tArbol* arbol, void(*accion)(const void*))///RID
{
    if(!(*arbol))
    {
        return;
    }
    accion((*arbol)->info);
    recorrerArbolPreOrden(&(*arbol)->izq,accion);
    recorrerArbolPreOrden(&(*arbol)->der,accion);
}


void recorrerArbolInOrden(tArbol* arbol, void(*accion)(const void*))///IRD
{
    if(!(*arbol))
    {
        return;
    }
    recorrerArbolInOrden(&(*arbol)->izq,accion);
    accion((*arbol)->info);
    recorrerArbolInOrden(&(*arbol)->der,accion);
}

void recorrerArbolPosOrden(tArbol* arbol, void(*accion)(const void*))///RID
{
    if(!(*arbol))
    {
        return;
    }
    recorrerArbolPreOrden(&(*arbol)->izq,accion);
    recorrerArbolPreOrden(&(*arbol)->der,accion);
    accion((*arbol)->info);
}

void rotarArbol(tArbol* arbol, void(*accion)(const void*, unsigned), unsigned nivel)
{
    if(!(*arbol))
    {
        return;
    }
    rotarArbol_90g(arbol, accion, nivel);
}


void rotarArbol_90g(tArbol* arbol, void(*accion)(const void*, unsigned), unsigned nivel)
{
    if(*arbol)
    {
        rotarArbol_90g(&(*arbol)->der, accion, nivel+1);
        accion((*arbol)->info, nivel);
        rotarArbol_90g(&(*arbol)->izq, accion, nivel+1);
    }
}


unsigned contarNodos(const tArbol* arbol)
{
    if(!*arbol)
        return 0;
    return (contarNodos(&(*arbol)->der)+ contarNodos(&(*arbol)->izq) + 1);
}

int alturaArbol(tArbol* arbol)
{
    int altIzq, altDer;
    if(!*arbol)
        return 0;

    altIzq = alturaArbol(&(*arbol)->izq);
    altDer = alturaArbol(&(*arbol)->der);
    return ((altIzq > altDer? altIzq: altDer)+1);
}


int esCompleto(tArbol* arbol)
{
    return esCompleto_aNiv(arbol, alturaArbol(arbol)-1);
}

int esBalanceado(tArbol* arbol)
{
    return esCompleto_aNiv(arbol, alturaArbol(arbol)-2);
}

int esCompleto_aNiv(tArbol* arbol, int nivel)
{
    if(!*arbol)
    {
        return (nivel<0);/// si manda un -1 le devuelvo un nro positivo
    }
    if(nivel == 0)
        return 1;
    return (esCompleto_aNiv(&(*arbol)->izq, nivel - 1) && esCompleto_aNiv(&(*arbol)->der, nivel - 1));
}

int esAVL(tArbol* arbol)
{
    int hi, hd;
    if(!*arbol)
        return 1;

    hi = alturaArbol(&(*arbol)->izq);
    hd = alturaArbol(&(*arbol)->der);
    if(abs(hi-hd)>1)
        return 0;
    return (esAVL(&(*arbol)->izq) && esAVL(&(*arbol)->der));
}

int eliminarNodoRaiz(tArbol* arbol)
{
    tNodoArbol* elim;
    tArbol* remp;
    int Hizq, Hder;

    if(!*arbol)
        return 0;

    free((*arbol)->info);

    if(!(*arbol)->izq && !(*arbol)->der)
    {
        free(*arbol);
        *arbol = NULL;
        return 1;
    }

    Hizq = alturaArbol(&(*arbol)->izq);
    Hder = alturaArbol(&(*arbol)->der);
    if(Hizq < Hder)
    {
        remp = menorNodoArbIzq(&(*arbol)->der);
    }
    else
    {
        remp = mayorNodoArbDer(&(*arbol)->izq);
    }

    (*arbol)->info = (*remp)->info;
    (*arbol)->tamInfo = (*remp)->tamInfo;
    elim = *remp;
    ((*remp) = (*remp)->izq? (*remp)->izq : (*remp)->der);
    free(elim);
    return 1;
}


tArbol* menorNodoArbIzq(const tArbol* arbol)
{
    if(!*arbol)
        return NULL;

    if(!(*arbol)->izq)
    {
        return (tArbol*)arbol;
    }
    menorNodoArbIzq(&(*arbol)->izq);
}


tArbol* mayorNodoArbDer(const tArbol* arbol)
{
    if(!*arbol)
        return NULL;

    if(!(*arbol)->der)
    {
        return (tArbol*)arbol;
    }
    mayorNodoArbDer(&(*arbol)->der);
}


int eliminarElemArbol(tArbol* arbol, void* dato, unsigned cantBytes, int(*comparar)(const void*, const void*))
{
    if(!(*arbol))
        return 0;

    if(!(arbol = buscarNodoArbol(arbol,dato,comparar)))
        return 0;
    memcpy(dato, (*arbol)->info, MINIMO(cantBytes,(*arbol)->tamInfo));
    return eliminarNodoRaiz(arbol);
}


tNodoArbol** buscarNodoArbol(const tArbol* arbol, void* dato,int(*comparar)(const void*, const void*))
{
    int cmp;

    if(!*arbol)
        return NULL;

    if(*arbol && (cmp = comparar(dato,(*arbol)->info)))
    {
        if(cmp < 0)
            return buscarNodoArbol(&(*arbol)->izq, dato, comparar);
        return buscarNodoArbol(&(*arbol)->der, dato, comparar);
    }
    return (tNodoArbol**)arbol;
}
