#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TDA_LISTA_IMPL_DINAMICA

#include "../Comun/Comun.h"
#include "E:\Universidad\Programacion\Practica para Parcial 1\2021-11-15_1erP_FacturacionElectro_Entregable\64Bits\TDALista\TDALista.h"
#include "../TDAListaImplDinamica/TDAListaImplDinamica.h"
#include "../SolucionFacturacionElectro/SolucionFacturacionElectro.h"

#define ARG_CLIENTES 1
#define ARG_MEDICIONES 2
#define ARG_FACTURAS 3
#define ARG_PROXIMO_NRO_FACTURA 4
#define ARG_CANT_MESES_A_FACTURAR 5

#define MAX_MESES 10

int extraerMesesAFacturar(char *argv[], Mes *mesesAFacturar);
int generarFacturas_ALU(const char *nombreArchivoClientes, const char *nombreArchivoMediciones, const char *nombreArchivoFacturas, int proximoNroFactura, const Mes *mesesAFacturar, int cantMesesAFacturar);
void cargarArchivoALista_alu(Lista *lista, const char *nomArch);
int Desglosado_alu(Medicion *medicion, char *linea);
int compararNroClientesMed_alu(const void *c1, const void *c2);
int compararNroClientesCli_alu(const void *c1, const void *c2);
void mostrarListaMediciones_alu(const Medicion *medicion);
int generarClienteAct_alu(Lista *lista, int nroCliente, char *nomCliente, const Fecha *ultMedicion, int valorMedido, const Mes *mesFacturado, double consumoMes);
//void mostrarArchClienteAct(const char* nombreArchivoClientes);

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

//			ret = generarFacturas(argv[ARG_CLIENTES], argv[ARG_MEDICIONES], argv[ARG_FACTURAS], atoi(argv[ARG_PROXIMO_NRO_FACTURA]), mesesAFacturar, cantMesesAFacturar);
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
	crearLista(&listaMediciones);
	cargarArchivoALista_alu(&listaMediciones, nombreArchivoMediciones);
	//	recorrerLista(&listaMediciones, mostrarListaMediciones_alu, &medicion);

	////Proceso los datos para generar la factura////////////
	double DM;
	int DD;
	double CDE;
	double CM;
	int cont = 0;
	int cont2 = 0;
	int ret = 0;
	Cliente cliente, clienteAct;
	Factura factura;
	Lista listaClienteAct;
	crearLista(&listaClienteAct);

	fread(&cliente, sizeof(Cliente), 1, archClientes);
	while (!feof(archClientes))
	{
		cont = cantMesesAFacturar;
		verPrimeroDeLista(&listaMediciones, &medicion, sizeof(Medicion));
		while (!listaVacia(&listaMediciones) && cont != 0)
		{
			if (cont == cantMesesAFacturar && mesesAFacturar[0].mes == medicion.fechaMedicion.mes)
			{
				DM = medicion.valorMedidor - cliente.valorMedidor;
				DD = (difEnDiasEntreFechas(&medicion.fechaMedicion, &cliente.fechaUltMedicion) * -1);
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

				eliminarDeListaPrimero(&listaMediciones, &medicion, sizeof(Medicion));
				cont--;
			}
			else if (cont == (cantMesesAFacturar - 1))///fijarse como validad  && mesesAFacturar[1].mes == medicion.fechaMedicion.mes
			{
				verPrimeroDeLista(&listaMediciones, &medicion, sizeof(Medicion));
				verPrimeroDeLista(&listaClienteAct, &clienteAct, sizeof(Cliente));


				DM = medicion.valorMedidor - clienteAct.valorMedidor;
				DD = (difEnDiasEntreFechas(&medicion.fechaMedicion, &clienteAct.fechaUltMedicion) * -1);
				CDE = DM / DD;
				CM = CDE * cantDiasMes(medicion.fechaMedicion.mes, medicion.fechaMedicion.anio);

				factura.nroFactura = proximoNroFactura + cont2++;
				factura.nroCliente = cliente.nroCliente;
				factura.fechaUltMedicion = medicion.fechaMedicion;
				factura.valorMedidor = medicion.valorMedidor;
				factura.mesFacturado = cont == 2 ? mesesAFacturar[0] : mesesAFacturar[1];
				factura.consumoMes = CM;
				fwrite(&factura, sizeof(Factura), 1, archFacturas);

                eliminarDeListaPrimero(&listaClienteAct, &clienteAct, sizeof(Cliente));
                ret = generarClienteAct_alu(&listaClienteAct, clienteAct.nroCliente, clienteAct.nombre, &factura.fechaUltMedicion, clienteAct.valorMedidor, &factura.mesFacturado, factura.consumoMes);
				if (ret != TODO_OK)
				{
					printf("Error al generar Cliente Actualizado\n");
					return ret;
				}
				verPrimeroDeLista(&listaClienteAct, &clienteAct, sizeof(Cliente));
				////actulizo el dato del cliente en el archivo
				cliente.fechaUltMedicion = clienteAct.fechaUltMedicion;
				cliente.valorMedidor = clienteAct.valorMedidor;
				cliente.ultMesFacturado = clienteAct.ultMesFacturado;
				cliente.ultConsumoMes = clienteAct.ultConsumoMes;
				fseek(archClientes, -(long)sizeof(Cliente), SEEK_CUR);
				fwrite(&cliente, sizeof(Cliente), 1, archClientes);
				fseek(archClientes, 0, SEEK_CUR);

				eliminarDeListaPrimero(&listaMediciones, &medicion, sizeof(Medicion));
				eliminarDeListaPrimero(&listaClienteAct, &clienteAct, sizeof(Cliente));
				cont--;
			}
		}

		fread(&cliente, sizeof(Cliente), 1, archClientes);
	}

//	mostrarArchClienteAct(nombreArchivoClientes);
	fclose(archFacturas);
	fclose(archClientes);
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
			insertarEnListaOrdCDup(lista, &medicion, sizeof(Medicion), compararNroClientesMed_alu);
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

	insertarEnListaOrdCDup(lista, &clienteAct, sizeof(Cliente), compararNroClientesCli_alu);

	return TODO_OK;
}


//void mostrarArchClienteAct(const char* nombreArchivoClientes)
//{
//    Cliente cli;
//    FILE* arch = fopen(nombreArchivoClientes, "rb");
//    if(!arch)
//    {
//        printf("No se pudo generar el archivo %s", nombreArchivoClientes);
//    }
//
//    fread(&cli, sizeof(Cliente), 1 , arch);
//    while(!feof(arch))
//    {
//        printf("%d| %s| %d/%d/%d| %d| %d/%d| %lf\n", cli.nroCliente, cli.nombre, cli.fechaUltMedicion.dia, cli.fechaUltMedicion.mes,
//               cli.fechaUltMedicion.anio, cli.valorMedidor, cli.ultMesFacturado.mes, cli.ultMesFacturado.anio, cli.ultConsumoMes);
//        fread(&cli, sizeof(Cliente), 1 , arch);
//    }
//}
