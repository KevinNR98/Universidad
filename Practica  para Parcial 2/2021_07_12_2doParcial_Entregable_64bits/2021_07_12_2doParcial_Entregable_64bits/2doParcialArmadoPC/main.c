#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../Solucion2doParcialArmadoPC/Solucion2doParcialArmadoPC.h"



#include "../TDAArbolImplDinamica/TDAArbolImplDinamica.h"
#include "../TDAArbol/TDAArbol.h"
#include "../TDAListaImplDinamicaDoble/TDAListaImplDinamicaDoble.h"
#include "../TDALista/TDALista.h"
#include "../TDA/TDA.h"
#include "../Solucion2doParcialArmadoPC/TiposArmadoPC.h"



int actualizarComponentes_alu(const char* pathComponentes, const char* pathArmadoYRep);
//void (*ImprimirElemArbol)(const void* elem, void* datosImprimir, int nivel);


int obtenerReg(ArmadoYRep* ayr, Arbol* idxComp);
void eliminarDuplicadosDeLista(Lista* aYrLista, Cmp cmp, Actualizar actualizar);
int cmpCod(const void* pv1, const void* pv2);
void actualizarAYR(void* pvpActualizado, const void* pvpActualizador);
int cmpAYR(const void* pv1, const void* pv2);
int eliminarDeListaPrimero2(Lista* armYrep,void* aYr, size_t ArmadoYRep);
int buscarEnListaDesord2(const Lista* armYrep,void* compont, size_t Componente,Cmp cmpCod);
void cargar_arbol_de_archivo_ordenado(Arbol* pa,size_t componente, const char* path);
int comparacion(const void *d1, const void *d2);
int tam_arch(FILE arch);
int generar_arbol_indice_rec(Arbol *pa, FILE arch_indice, int li, int ls);
int insertar_en_arbol_bin_busq(Arbol pa, const void* pd, Cmp comp);



/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
int insertarEnListaOrd_ALU(Lista *pl, void *elem, size_t tamElem, Cmp cmp);
void crearLista_ALU(Lista *pl);
int listaVacia_ALU(const Lista* lista);
int insertarYActEnListaOrd_ALU(Lista *pl, void *elem, size_t tamElem, Cmp cmp, Actualizar actualizar);
//////////////////////////////////////////////////////////////////////////////////////////////////////

int cargarArbolDeArchOrd_ALU(Arbol* pa, Cmp cmp);
int cargarArbol_ALU(FILE* arch, Arbol* pa, int li, int ls, Cmp cmp);


int insertarEnArbol_ALU(Arbol *pa, const void *elem, size_t tamElem, Cmp cmp);
int buscarEnArbol_ALU(const Arbol *pa, void *elem, size_t tamElem, Cmp cmp);
int esArbolBalanceado_ALU(const Arbol* pa);


/////////////////////////////////////////


int cargarAyREnLista_ALU(const char* nomArch, Lista* lista);
int cmpCodigoIdx(const void* a, const void* b);
int cmpNroReg(const void* a, const void* b);
void actualizarAYR_ALU(void* pvpActualizado, const void* pvpActualizador);
int cmpCodArYRep(const void* a, const void* b);


#define ARG_PATH_COMP 1
#define ARG_PATH_ARM_REP 2


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "spanish");	// Cambiar locale - Suficiente para máquinas Linux
    SetConsoleCP(1252); 			// Cambiar STDIN -  Para máquinas Windows
    SetConsoleOutputCP(1252);		// Cambiar STDOUT - Para máquinas Windows

    generarArchivoStockComponentes(argv[ARG_PATH_COMP]);

    generarArchivoArmadosYReparaciones(argv[ARG_PATH_ARM_REP]);

    puts("Componentes antes de actualizar:\n");
    mostrarArchivoComponentes(argv[ARG_PATH_COMP]);
    puts("");

    puts("Armados/Reparaciones:");
    mostrarArchivoArmadoYRep(argv[ARG_PATH_ARM_REP]);
    puts("");
//    int resp = actualizarComponentes(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
    ///************************************************************************************
    ///******** Descomente esta línea y comente la de arriba para probar su código ********
    int resp = actualizarComponentes_alu(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
    ///************************************************************************************

    if(resp != TODO_OK)
    {
        puts("Error actualizando los componentes.");
        return resp;
    }


    puts("\nComponentes despues de actualizar:\n");
    mostrarArchivoComponentes(argv[ARG_PATH_COMP]);

    return 0;
}



int actualizarComponentes_alu(const char* pathComponentes, const char* pathArmadoYRep)
{
    Arbol idxArbol;
    Lista AyRLista;
    crearArbol(&idxArbol);
    crearLista_ALU(&AyRLista);

//    cargarIndiceA_Arbol_ALU(&idxArbol, &idxLista);
    cargarArbolDeArchOrd_ALU(&idxArbol, cmpCodigoIdx);
    cargarAyREnLista_ALU(pathArmadoYRep, &AyRLista);

    int ret = arbolBalanceado(&idxArbol);
    if(ret)
    {
        printf("EL ARBOL ESTA BALANCEADO\n");
    }
    else
    {
        printf("ERROR EL ARBOL NO ESTA BALANCEADO\n");
    }

    Componente comp;
    ArmadoYRep armYRep;
    IndComponente idx;

    FILE* archComp = fopen(pathComponentes, "rb+");
    if(!archComp)
        return ERROR;


    eliminarDeListaPrimero(&AyRLista, &armYRep, sizeof(ArmadoYRep));
    strcpy(idx.codigo, armYRep.codigo);
    while(!listaVacia_ALU(&AyRLista))
    {
        if(buscarEnArbol_ALU(&idxArbol, &idx, sizeof(IndComponente), cmpCodigoIdx) == 1)
        {
            fseek(archComp, idx.nroReg*sizeof(Componente), SEEK_SET);
            fread(&comp, sizeof(Componente), 1, archComp);

            comp.stock -= armYRep.cantidad;

            fseek(archComp, idx.nroReg*sizeof(Componente), SEEK_SET);
            fwrite(&comp, sizeof(Componente), 1, archComp);
        }
        eliminarDeListaPrimero(&AyRLista, &armYRep, sizeof(ArmadoYRep));
        strcpy(idx.codigo, armYRep.codigo);
    }

    if(buscarEnArbol_ALU(&idxArbol, &idx, sizeof(IndComponente), cmpCodigoIdx) == 1)
    {
        fseek(archComp, idx.nroReg*sizeof(Componente), SEEK_SET);
        fread(&comp, sizeof(Componente), 1, archComp);

        comp.stock -= armYRep.cantidad;

        fseek(archComp, idx.nroReg*sizeof(Componente), SEEK_SET);
        fwrite(&comp, sizeof(Componente), 1, archComp);
    }

///	Resolver.
/// Nota: Resuelva esta, y todas las funciones que necesite, en este archivo. Que será el que debe entregar. No modifique ni entregue otro/s archivos del proyecto.
/// Agregue el sufijo "_alu" a todas las funciones que genere.FILE* bin;

    fclose(archComp);
    return TODO_OK;
}


///////////////////////////////////////////////////////////////////////////////////////

int cargarArbolDeArchOrd_ALU(Arbol* pa, Cmp cmp)
{
    int tamArchBytes = 0, cantReg = 0;

    FILE* archIdx = fopen("Componentes.idx", "rb");
    if(!archIdx)
        return ERROR;

    fseek(archIdx, 0L, SEEK_END);
    tamArchBytes = ftell(archIdx);
    cantReg = tamArchBytes / sizeof(IndComponente);

    int li = 0, ls = cantReg - 1;

    cargarArbol_ALU(archIdx, pa, li, ls, cmpCodigoIdx);

    fclose(archIdx);

    return TODO_OK;
}



int cargarArbol_ALU(FILE* arch, Arbol* pa, int li, int ls, Cmp cmp)
{
    IndComponente idx;

    if(li>ls)
        return VERDADERO;

    int m = (li + ls)/2;

    fseek(arch, m * sizeof(IndComponente), SEEK_SET);
    fread(&idx, sizeof(IndComponente), 1, arch);
    insertarEnArbol_ALU(pa, &idx, sizeof(IndComponente), cmpCodigoIdx);

    return cargarArbol_ALU(arch, &(*pa)->hIzq, li, m - 1, cmp) && cargarArbol_ALU(arch, &(*pa)->hDer, m + 1, ls, cmp);
}


int cargarAyREnLista_ALU(const char* nomArch, Lista* lista)
{
    ArmadoYRep ArYRep;

    FILE* archArYRep = fopen(nomArch, "rb");
    if(!archArYRep)
        return ERROR;

    fread(&ArYRep, sizeof(ArmadoYRep), 1, archArYRep);
    while(!feof(archArYRep))
    {
        insertarYActEnListaOrd_ALU(lista, &ArYRep, sizeof(ArmadoYRep), cmpCodArYRep, actualizarAYR_ALU);
        fread(&ArYRep, sizeof(ArmadoYRep), 1, archArYRep);
    }

    fclose(archArYRep);

    return TODO_OK;
}



int cmpCodigoIdx(const void* a, const void* b)
{
    return strcmp(((IndComponente*)a)->codigo, ((IndComponente*)b)->codigo);
}

int cmpNroReg(const void* a, const void* b)
{
    return ((IndComponente*)a)->nroReg - ((IndComponente*)b)->nroReg;
}

void actualizarAYR_ALU(void* pvpActualizado, const void* pvpActualizador)
{
    ((ArmadoYRep*)pvpActualizado)->cantidad += ((ArmadoYRep*)pvpActualizador)->cantidad;
    ((ArmadoYRep*)pvpActualizado)->precioUnitario = ((ArmadoYRep*)pvpActualizador)->precioUnitario;
    ((ArmadoYRep*)pvpActualizado)->nroOp = ((ArmadoYRep*)pvpActualizador)->nroOp;
}

int cmpCodArYRep(const void* a, const void* b)
{
    return strcmp(((ArmadoYRep*)a)->codigo, ((ArmadoYRep*)b)->codigo);
}

////////////////////////////////////////////////////////////////////////////////////////

void crearLista_ALU(Lista *pl)
{
    *pl = NULL;
}


int insertarYActEnListaOrd_ALU(Lista *pl, void *elem, size_t tamElem, Cmp cmp, Actualizar actualizar)
{
    NodoD *act = *pl, *ant, *sig;

    if (act == NULL)
    {
        ant = sig = NULL;
    }
    else
    {
        while (act->sig && cmp(elem, act->dato) > 0) //Avanzo hacia la derecha
            act = act->sig;

        while (act->ant && cmp(elem, act->dato) < 0) //Avanzo hacia la izquierda
            act = act->ant;

        int comp = cmp(elem, act->dato);

        if (comp == 0)
        {
            actualizar(act->dato, elem);
            return DUPLICADO;
        }


        if(comp < 0)
        {
            ant = act->ant;
            sig = act;
        }
        else
        {
            ant = act;
            sig = act->sig;
        }
    }

    NodoD* nuevo = malloc(sizeof(NodoD));
    void* nuevoElem = malloc(tamElem);

    if(!nuevo || !nuevoElem)
    {
        free(nuevo);
        free(nuevoElem);
        return ERROR;
    }

    memcpy(nuevoElem, elem, tamElem);
    nuevo->dato = nuevoElem;
    nuevo->tamElem = tamElem;

    nuevo->ant = ant;//1
    nuevo->sig = sig;//2

    if(ant)
        ant->sig = nuevo;//3

    if(sig)
        sig->ant = nuevo;

    *pl = nuevo;

    return TODO_OK;
}


int listaVacia_ALU(const Lista* lista)
{
    return *lista == NULL;
}
//////////////////////////////////////////////////////////////////////////////////////

int insertarEnArbol_ALU(Arbol *pa, const void *elem, size_t tamElem, Cmp cmp)
{
    if (!*pa)
    {
        NodoA *nuevo = malloc(sizeof(NodoA));
        void *elemNuevo = malloc(tamElem);

        if (!nuevo || !elemNuevo)
        {
            free(nuevo);
            free(elemNuevo);
            return ERROR;
        }

        memcpy(elemNuevo, elem, tamElem);
        nuevo->dato = elemNuevo;
        nuevo->tamElem = tamElem;
        nuevo->hIzq = nuevo->hDer = NULL;

        *pa = nuevo;
    }

    int comp = cmp(elem, (*pa)->dato);

    if(comp == 0)
        return DUPLICADO;

    return  insertarEnArbol_ALU(comp < 0? &(*pa)->hIzq : &(*pa)->hDer, elem, tamElem, cmp);
}



int buscarEnArbol_ALU(const Arbol *pa, void *elem, size_t tamElem, Cmp cmp)
{
    if(!*pa)
        return FALSO;

    int comp = cmp(elem, (*pa)->dato);

    if(comp == 0)
    {
        memcpy(elem,(*pa)->dato, min(tamElem, (*pa)->tamElem));
        return VERDADERO;
    }

    return buscarEnArbol_ALU(comp < 0? &(*pa)->hIzq : &(*pa)->hDer, elem, tamElem, cmp);
}
