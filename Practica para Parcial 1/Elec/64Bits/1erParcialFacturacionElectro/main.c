#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Nodo/Nodo.h"
#include "../TDAListaImplDinamica/TDAListaImplDinamica.h"
#include "../Comun/Comun.h"
#include "../SolucionFacturacionElectro/SolucionFacturacionElectro.h"

#define ARG_CLIENTES 1
#define ARG_MEDICIONES 2
#define ARG_FACTURAS 3
#define ARG_PROXIMO_NRO_FACTURA 4
#define ARG_CANT_MESES_A_FACTURAR 5

#define min(x, y) ((x) < (y)? (x) : (y))

#define MAX_MESES 10

int extraerMesesAFacturar(char *argv[], Mes *mesesAFacturar);
int generarFacturas_ALU(const char *nombreArchivoClientes, const char *nombreArchivoMediciones, const char *nombreArchivoFacturas, int proximoNroFactura, const Mes *mesesAFacturar, int cantMesesAFacturar);
void cargarArchivoALista_alu(Lista *lista, const char *nomArch);
int Desglosado_alu(Medicion *medicion, char *linea);
int compararNroClientesMed_alu(const void *c1, const void *c2);
int compararNroClientesCli_alu(const void *c1, const void *c2);
void mostrarListaMediciones_alu(const Medicion *medicion);
int generarClienteAct_alu(Lista *lista, int nroCliente, char *nomCliente, const Fecha *ultMedicion, int valorMedidor, const Mes *mesFacturado, double consumoMes);
int obtenerConsmoMesSig(Cliente* cli, Medicion* med);
/////////////////LISTA/////////////////////////////////////
void crearLista_alu(Lista *lista);
int listaVacia_alu(const Lista *lista);
int listaLlena_alu(const Lista *lista, size_t tamElem);
int insertarEnListaOrdCDup_alu(Lista *pl, const void *elem, size_t tamElem, Cmp cmp);
int verPrimeroDeLista_alu(Lista* lista, const void* elem, size_t tamElem);
int eliminarDeListaPrimero_alu(Lista* lista, void* elem, size_t tamElem);

int main(int argc, char *argv[])
{
    int ret = generarArchivos();

    if (ret != TODO_OK)
    {
        printf("Error al generar archivos\n");
        return ret;
    }

    printf("Archivos generados correctamente\n");

    puts("\nAntes de Actualizar:\n");

    mostrarClientes(argv[ARG_CLIENTES]);

    mostrarMediciones(argv[ARG_MEDICIONES]);

    Mes mesesAFacturar[MAX_MESES];

    int cantMesesAFacturar = extraerMesesAFacturar(argv, mesesAFacturar);

//    ret = generarFacturas(argv[ARG_CLIENTES], argv[ARG_MEDICIONES], argv[ARG_FACTURAS], atoi(argv[ARG_PROXIMO_NRO_FACTURA]), mesesAFacturar, cantMesesAFacturar);
    /// Descomente esta línea y comente la de arriba, para ejecutar su código
    ret = generarFacturas_ALU(argv[ARG_CLIENTES], argv[ARG_MEDICIONES], argv[ARG_FACTURAS], atoi(argv[ARG_PROXIMO_NRO_FACTURA]), mesesAFacturar, cantMesesAFacturar);

    if (ret != TODO_OK)
    {
        printf("Error al generar facturas\n");
        return ret;
    }

    puts("\nDespues de Actualizar:\n");

    mostrarFacturas(argv[ARG_FACTURAS]);

    mostrarClientes(argv[ARG_CLIENTES]);

    return ret;
}

int extraerMesesAFacturar(char *argv[], Mes *mesesAFacturar)
{
    int cantMesesAFacturar = atoi(argv[ARG_CANT_MESES_A_FACTURAR]);

    for (int i = 0; i < cantMesesAFacturar; i++)
        mesesAFacturar[i] = strToMes(argv[ARG_CANT_MESES_A_FACTURAR + 1 + i]);

    return cantMesesAFacturar;
}

int generarFacturas_ALU(const char *nombreArchivoClientes, const char *nombreArchivoMediciones, const char *nombreArchivoFacturas, int proximoNroFactura, const Mes *mesesAFacturar, int cantMesesAFacturar)
{
    int cmp = 0;

    Cliente cli;
    Medicion med;
    Lista listaMed;
    crearLista_alu(&listaMed);

    FILE* archCli = fopen(nombreArchivoClientes, "rb");
    if(!archCli)
        return ERR_ARCHIVO;

    FILE* archFact = fopen(nombreArchivoFacturas, "wb");
    if(!archFact)
        return ERR_ARCHIVO;

    cargarArchivoALista_alu(&listaMed, nombreArchivoMediciones);

    fread(&cli, sizeof(Cliente),1, archCli);
    verPrimeroDeLista_alu(&listaMed, &med, sizeof(Medicion));
    while(!feof(archCli))
    {
        cmp = cli.nroCliente - med.nroCliente;
        if(cmp == 0)
        {
            obtenerConsmoMesSig(&cli, &med);
        }
    }

}


void cargarArchivoALista_alu(Lista* pl, const char* nomArch)
{
    Medicion med;
    FILE* archMed = fopen(nomArch, "rt");
    if(!archMed)
        return ERR_ARCHIVO;

    while(fscanf(archMed, "%d|%d/%d/%d|%d\n", &med.nroCliente, &med.fechaMedicion.dia, &med.fechaMedicion.mes, &med.fechaMedicion.anio, &med.valorMedidor) != EOF)
    {
        insertarEnListaOrdCDup_alu(pl, &med, sizeof(Medicion), compararNroClientesMed_alu);
    }

    fclose(archMed);
}


int obtenerConsmoMesSig(Cliente* cli, Medicion* med)
{
    int DM = med->valorMedidor - cli->valorMedidor;

    return TODO_OK;
}

int compararNroClientesMed_alu(const void* c1, const void* c2)
{
    return ((Medicion*)c1)->nroCliente - ((Medicion*)c2)->nroCliente;
}



//////////////////////Lista//////////////////////////////////////

void crearLista_alu(Lista* pl)
{
    *pl = NULL;
}

int insertarEnListaOrdCDup_alu(Lista* pl, const void* elem, size_t tamElem, Cmp cmp)
{
    Nodo* nue;
    size_t elemNodo;

    while(*pl && cmp(elem, (*pl)->elem) > 0)
        pl = &(*pl)->sig;

    if(*pl && cmp(elem, (*pl)->elem) == 0)
        pl = &(*pl)->sig;

    nue = malloc(sizeof(Nodo));
    elemNodo = malloc(tamElem);

    if(!nue || !elemNodo)
    {
        free(nue);
        free(elemNodo);
        return SIN_MEM;
    }

    memcpy(elemNodo, elem, tamElem);
    nue->elem = elemNodo;
    nue->tamElem = tamElem;


    nue->sig = *pl;
    *pl = nue;

    return TODO_OK;
}


int sacarDeListaOrdCDup_alu(Lista* pl, void* elem, size_t tamElem, Cmp cmp)
{
    Nodo* nae;;

    while(*pl && cmp(elem, (*pl)->elem) > 0)
        pl = &(*pl)->sig;

    while(!*pl || cmp(elem, (*pl)->elem) < 0)
        return falso;

    nae = *pl;
    *pl = nae->sig;
    memcpy(elem, nae->elem, min(tamElem, nae->tamElem));

    free(nae->elem);
    free(nae);

    return TODO_OK;
}

int verPrimeroDeLista_alu(Lista* pl, const void* elem, size_t tamElem)
{
    if(!*pl)
        return falso;

    memcpy(elem, (*pl)->elem, min(tamElem, (*pl)->tamElem));

    return verdadero;
}


int eliminarDeListaPrimero_alu(Lista* pl, void* elem, size_t tamElem)
{
    Nodo* nae;

    if(!*pl)
        return falso;

    nae = *pl;
    *pl = nae->sig;
    memcpy(elem, nae->elem, min(tamElem, nae->elem));

    free(nae->elem);
    free(nae);
    return TODO_OK;
}


int listaLlena_alu(const Lista* pl, size_t tamElem)
{
    Nodo* nue = malloc(sizeof(Nodo));
    size_t elemNodo = malloc(tamElem);

    free(nue);
    free(elemNodo);
    return !nue || !elemNodo;
}

int listaVacia_alu(const Lista* pl)
{
    return !*pl;
}
