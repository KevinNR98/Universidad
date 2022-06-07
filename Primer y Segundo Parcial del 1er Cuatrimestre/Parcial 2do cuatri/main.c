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
/////////////////LISTA/////////////////////////////////////
void crearLista_alu(Lista *lista);
int listaVacia_alu(const Lista *lista);
int listaLlena_alu(const Lista *lista, size_t tamElem);
int insertarEnListaOrdCDup_alu(Lista *pl, const void *elem, size_t tamElem, Cmp cmp);
int verPrimeroDeLista_alu(Lista* lista, void* dato, size_t tamElem);
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

//		ret = generarFacturas(argv[ARG_CLIENTES], argv[ARG_MEDICIONES], argv[ARG_FACTURAS], atoi(argv[ARG_PROXIMO_NRO_FACTURA]), mesesAFacturar, cantMesesAFacturar);
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
    Medicion medicion;
    FILE *archClientes = fopen(nombreArchivoClientes, "r+b");
    if (!archClientes)
    {
        printf("El archivo %s no se pudo crear correctamente\n", nombreArchivoClientes);
        return ERR_ARCHIVO;
    }

    FILE *archFacturas = fopen(nombreArchivoFacturas, "wb");
    if (!archFacturas)
    {
        printf("El archivo %s no se pudo crear correctamente\n", nombreArchivoFacturas);
        return ERR_ARCHIVO;
    }

    Lista listaMediciones;
    crearLista_alu(&listaMediciones);
    cargarArchivoALista_alu(&listaMediciones, nombreArchivoMediciones);
    //recorrerLista(&listaMediciones, mostrarListaMediciones_alu, &medicion);

    ////Proceso los datos para generar la factura////////////
    double DM;
    int DD;
    double CDE;
    double CM;
    int cont = 0;
    int cont2 = 0;
    int ret = 0;
    int noEx = 0;
    Cliente cliente, clienteAct;
    Factura factura;
    Lista listaClienteAct;
    crearLista_alu(&listaClienteAct);
    Medicion med;///para guardar los valores, si los necesito

    fread(&cliente, sizeof(Cliente), 1, archClientes);
    while (!feof(archClientes))
    {
        cont = cantMesesAFacturar;
        while (!listaVacia_alu(&listaMediciones) && cont != 0)
        {
            verPrimeroDeLista_alu(&listaMediciones, &medicion, sizeof(Medicion));
            if (cont == cantMesesAFacturar && cliente.nroCliente == medicion.nroCliente && mesesAFacturar[0].mes == medicion.fechaMedicion.mes)
            {
                DM = medicion.valorMedidor - cliente.valorMedidor;
                DD = (difEnDiasEntreFechas(&medicion.fechaMedicion, &cliente.fechaUltMedicion) * - 1);
                CDE = DM / DD;
                CM = CDE * cantDiasMes(medicion.fechaMedicion.mes, medicion.fechaMedicion.anio);

                factura.nroFactura = proximoNroFactura + cont2++;
                factura.nroCliente = cliente.nroCliente;
                factura.fechaUltMedicion = medicion.fechaMedicion;
                factura.valorMedidor = medicion.valorMedidor;
                factura.mesFacturado = cont == 2 ? mesesAFacturar[0] : mesesAFacturar[1];
                factura.consumoMes = CM;
                fwrite(&factura, sizeof(Factura), 1, archFacturas);

                ret = generarClienteAct_alu(&listaClienteAct, cliente.nroCliente, cliente.nombre, &factura.fechaUltMedicion, factura.valorMedidor, &factura.mesFacturado, factura.consumoMes);
                if (ret != TODO_OK)
                {
                    printf("Error al generar Cliente Actualizado\n");
                    return ret;
                }

                med = medicion;
                eliminarDeListaPrimero_alu(&listaMediciones, &medicion, sizeof(Medicion));
                cont--;
            }

            if(mesesAFacturar[0].mes != medicion.fechaMedicion.mes && cont == cantMesesAFacturar)
            {
                DM = medicion.valorMedidor - cliente.valorMedidor;
                DD = (difEnDiasEntreFechas(&medicion.fechaMedicion, &cliente.fechaUltMedicion) * - 1);
                CDE = DM / DD;
                CM = CDE * cantDiasMes(mesesAFacturar[0].mes, medicion.fechaMedicion.anio);

                factura.nroFactura = proximoNroFactura + cont2++;
                factura.nroCliente = cliente.nroCliente;
                factura.fechaUltMedicion = medicion.fechaMedicion;
                factura.valorMedidor = medicion.valorMedidor;
                factura.mesFacturado = cont == 2 ? mesesAFacturar[0] : mesesAFacturar[1];
                factura.consumoMes = CM;
                fwrite(&factura, sizeof(Factura), 1, archFacturas);

                ret = generarClienteAct_alu(&listaClienteAct, cliente.nroCliente, cliente.nombre, &factura.fechaUltMedicion, factura.valorMedidor, &factura.mesFacturado, factura.consumoMes);
                if (ret != TODO_OK)
                {
                    printf("Error al generar Cliente Actualizado\n");
                    return ret;
                }
                noEx = 1;
                cont--;
            }


            if (cont == (cantMesesAFacturar - 1) && cliente.nroCliente == medicion.nroCliente && mesesAFacturar[1].mes == medicion.fechaMedicion.mes)
            {

                verPrimeroDeLista_alu(&listaMediciones, &medicion, sizeof(Medicion));
                verPrimeroDeLista_alu(&listaClienteAct, &clienteAct, sizeof(Cliente));
                if(noEx == 1)
                {
                    clienteAct.fechaUltMedicion.mes = 10;
                    DD = (difEnDiasEntreFechas(&medicion.fechaMedicion, &clienteAct.fechaUltMedicion) * - 1);
                    CDE = CM / DD;
                    CM = CDE * cantDiasMes(medicion.fechaMedicion.mes, medicion.fechaMedicion.anio);
                    noEx = 0;
                }
                else
                {
                    DM = medicion.valorMedidor - clienteAct.valorMedidor;
                    DD = (difEnDiasEntreFechas(&medicion.fechaMedicion, &clienteAct.fechaUltMedicion) * -1);
                    CDE = DM / DD;
                    CM = CDE * cantDiasMes(medicion.fechaMedicion.mes, medicion.fechaMedicion.anio);
                }


                factura.nroFactura = proximoNroFactura + cont2++;
                factura.nroCliente = cliente.nroCliente;
                factura.fechaUltMedicion = medicion.fechaMedicion;
                factura.valorMedidor = medicion.valorMedidor;
                factura.mesFacturado = cont == 2 ? mesesAFacturar[0] : mesesAFacturar[1];
                factura.consumoMes = CM;
                fwrite(&factura, sizeof(Factura), 1, archFacturas);

                eliminarDeListaPrimero_alu(&listaClienteAct, &clienteAct, sizeof(Cliente));
                ret = generarClienteAct_alu(&listaClienteAct, clienteAct.nroCliente, clienteAct.nombre, &factura.fechaUltMedicion, clienteAct.valorMedidor, &factura.mesFacturado, factura.consumoMes);
                if (ret != TODO_OK)
                {
                    printf("Error al generar Cliente Actualizado\n");
                    return ret;
                }
                verPrimeroDeLista_alu(&listaClienteAct, &clienteAct, sizeof(Cliente));
                ////actulizo el dato del cliente en el archivo
                cliente.fechaUltMedicion = clienteAct.fechaUltMedicion;
                cliente.valorMedidor = clienteAct.valorMedidor;
                cliente.ultMesFacturado = clienteAct.ultMesFacturado;
                cliente.ultConsumoMes = clienteAct.ultConsumoMes;
                fseek(archClientes, -(long)sizeof(Cliente), SEEK_CUR);
                fwrite(&cliente, sizeof(Cliente), 1, archClientes);
                fseek(archClientes, 0, SEEK_CUR);

                eliminarDeListaPrimero_alu(&listaMediciones, &medicion, sizeof(Medicion));
                eliminarDeListaPrimero_alu(&listaClienteAct, &clienteAct, sizeof(Cliente));
                cont--;
            }

            if(mesesAFacturar[1].mes != medicion.fechaMedicion.mes && cont == cantMesesAFacturar - 1 && cliente.nroCliente != medicion.nroCliente)
            {
                verPrimeroDeLista_alu(&listaClienteAct, &clienteAct, sizeof(Cliente));

                med.fechaMedicion.mes = 11;
                DD = (difEnDiasEntreFechas(&med.fechaMedicion, &clienteAct.fechaUltMedicion) * -1);
                CDE = CM / DD;
                CM = CDE * cantDiasMes(med.fechaMedicion.mes, medicion.fechaMedicion.anio);

                factura.nroFactura = proximoNroFactura + cont2++;
                factura.nroCliente = cliente.nroCliente;
                factura.fechaUltMedicion = medicion.fechaMedicion;
                factura.valorMedidor = medicion.valorMedidor;
                factura.mesFacturado = cont == 2 ? mesesAFacturar[0] : mesesAFacturar[1];
                factura.consumoMes = CM;
                fwrite(&factura, sizeof(Factura), 1, archFacturas);

                eliminarDeListaPrimero_alu(&listaClienteAct, &clienteAct, sizeof(Cliente));
                ret = generarClienteAct_alu(&listaClienteAct, clienteAct.nroCliente, clienteAct.nombre, &factura.fechaUltMedicion, clienteAct.valorMedidor, &factura.mesFacturado, factura.consumoMes);
                if (ret != TODO_OK)
                {
                    printf("Error al generar Cliente Actualizado\n");
                    return ret;
                }
                verPrimeroDeLista_alu(&listaClienteAct, &clienteAct, sizeof(Cliente));
                ////actulizo el dato del cliente en el archivo
                cliente.fechaUltMedicion = clienteAct.fechaUltMedicion;
                cliente.valorMedidor = clienteAct.valorMedidor;
                cliente.ultMesFacturado = clienteAct.ultMesFacturado;
                cliente.ultConsumoMes = clienteAct.ultConsumoMes;
                fseek(archClientes, -(long)sizeof(Cliente), SEEK_CUR);
                fwrite(&cliente, sizeof(Cliente), 1, archClientes);
                fseek(archClientes, 0, SEEK_CUR);

                eliminarDeListaPrimero_alu(&listaClienteAct, &clienteAct, sizeof(Cliente));
                cont--;

            }
        }

        fread(&cliente, sizeof(Cliente), 1, archClientes);
    }

    //	mostrarArchClienteAct(nombreArchivoClientes);
    fclose(archFacturas);
    fclose(archClientes);
    return TODO_OK;

    return TODO_OK;
}

void cargarArchivoALista_alu(Lista *lista, const char *nomArch)
{
    Medicion medicion;
    char linea[50];
    FILE *archMediciones = fopen(nomArch, "rt");
    if (!archMediciones)
    {
        printf("Error al abrir el archivo %s", nomArch);
    }

    while (fgets(linea, 50, archMediciones))
    {
        if (!Desglosado_alu(&medicion, linea))
        {
            insertarEnListaOrdCDup_alu(lista, &medicion, sizeof(Medicion), compararNroClientesMed_alu);
        }
    }

    fclose(archMediciones);
}

int Desglosado_alu(Medicion *medicion, char *linea)
{
    char *marcador;
    /////Valor medidor
    if ((marcador = strrchr(linea, '|')) == NULL)
    {
        return ERR_ARCHIVO;
    }
    sscanf(marcador + 1, "%d", &(medicion)->valorMedidor);
    *marcador = '\0';

    ////Fecha
    if ((marcador = strrchr(linea, '|')) == NULL)
    {
        return ERR_ARCHIVO;
    }
    sscanf(marcador + 1, "%d/%d/%d", &medicion->fechaMedicion.dia, &medicion->fechaMedicion.mes, &medicion->fechaMedicion.anio);
    *marcador = '\0';
    ///Nro Cliente
    sscanf(linea, "%d", &medicion->nroCliente);

    return TODO_OK;
}

int compararNroClientesMed_alu(const void *c1, const void *c2)
{
    return ((Medicion *)c1)->nroCliente - ((Medicion *)c2)->nroCliente;
}

int compararNroClientesCli_alu(const void *c1, const void *c2)
{
    return ((Cliente *)c1)->nroCliente - ((Cliente *)c2)->nroCliente;
}

void mostrarListaMediciones_alu(const Medicion *medicion)
{
    printf("%d %d/%d/%d %d\n", medicion->nroCliente, medicion->fechaMedicion.dia, medicion->fechaMedicion.mes, medicion->fechaMedicion.anio, medicion->valorMedidor);
}

int generarClienteAct_alu(Lista *lista, int nroCliente, char *nomCliente, const Fecha *ultMedicion, int valorMedidor, const Mes *mesFacturado, double consumoMes)
{
    Cliente clienteAct;

    clienteAct.nroCliente = nroCliente;
    strcpy(clienteAct.nombre, nomCliente);
    clienteAct.fechaUltMedicion = *ultMedicion;
    clienteAct.valorMedidor = valorMedidor;
    clienteAct.ultMesFacturado = *mesFacturado;
    clienteAct.ultConsumoMes = consumoMes;

    insertarEnListaOrdCDup_alu(lista, &clienteAct, sizeof(Cliente), compararNroClientesCli_alu);

    return TODO_OK;
}

////////////////////////////////////PRIMITTIVAS DE LISTA/////////////////////
void crearLista_alu(Lista *lista)
{
    *lista = NULL;
}

int listaVacia_alu(const Lista *lista)
{
    return *lista == NULL;
}

int listaLlena_alu(const Lista *lista, size_t tamElem)
{
    Nodo *aux = malloc(sizeof(Nodo));
    if (!aux)
        return 1;
    aux->elem = malloc(tamElem);
    if (!aux->elem)
        free(aux);
    return 1;

    free(aux->elem);
    free(aux);
    return 0;
}



int insertarEnListaOrdCDup_alu(Lista *pl, const void *elem, size_t tamElem, Cmp cmp)
{
    Nodo *nue;
    void *elemNodo;

    while (*pl && cmp(elem, (*pl)->elem) > 0)
        pl = &(*pl)->sig;

    if (*pl && cmp(elem, (*pl)->elem) == 0)
        pl = &(*pl)->sig;

    nue = malloc(sizeof(Nodo));
    elemNodo = malloc(tamElem);

    if (!nue || !elemNodo)
    {
        free(nue);
        free(elemNodo);
        return 1;
    }

    nue->elem = elemNodo;
    memcpy(elemNodo, elem, tamElem);
    nue->tamElem = tamElem;

    nue->sig = *pl;
    *pl = nue;

    return TODO_OK;
}


int verPrimeroDeLista_alu(Lista* lista, void* dato, size_t tamElem)
{
    if(*lista == NULL)
        return 0;

    memcpy(dato, (*lista)->elem, min(tamElem, (*lista)->tamElem));
    return 1;
}


int eliminarDeListaPrimero_alu(Lista* lista, void* elem, size_t tamElem)
{
    Nodo* aux = *lista;

    if(aux == NULL)
        return 0;

    *lista = aux->sig;

    free(aux->elem);
    free(aux);
    return 1;
}
