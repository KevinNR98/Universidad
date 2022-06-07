#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <E:\Universidad\Programacion\Practica para Parcial 1\Resueltos\ParcialDeliveryResuelto\deliveryResuelto.h>
#include <E:\Universidad\Programacion\Practica para Parcial 1\Resueltos\ParcialDeliveryResuelto\TiposDelivery.h>
#include <E:\Universidad\Programacion\Practica para Parcial 1\Resueltos\ParcialDeliveryResuelto\TipoTDA.h>
#include <E:\Universidad\Programacion\Practica para Parcial 1\Resueltos\ParcialDeliveryResuelto\Cola.h>


int main()
{
    FILE* arch_pedidos = fopen("Pedidos.txt", "rt");
    FILE* arch_recetas = fopen("Recetas.dat", "r+b");
    FILE* arch_ingredientes = fopen("Ingredientes.dat", "r+b");

    if(!arch_pedidos || !arch_recetas || !arch_ingredientes)
    {
        puts("Error en la apertura de los archivos");
        return 1;
    }
    puts("Archivo Pedidos:");
    mostrar_archivo_pedidos(arch_pedidos);
    puts("\nArchivo Recetas:");
    mostrar_archivo_recetas(arch_recetas);

    puts("\nIngredientes antes de la actualizacion:");
    mostrar_archivo_ingredientes(arch_ingredientes);

    ///satisfacer_pedidos(arch_pedidos, arch_recetas, arch_ingredientes, vec_ind_rec, ce_ind_rec, vec_ind_ingr, ce_ind_ingr);

	puts("Ingredientes despues de la actualizacion");
	mostrar_archivo_ingredientes(arch_ingredientes);

	fclose(arch_pedidos);
	fclose(arch_recetas);
	fclose(arch_ingredientes);

    return 0;
}


///////MOSTRAR ARCHIVOS/////////////////////////////////////

void mostrar_archivo_pedidos(FILE* arch_pedidos)
{
    char vecPedidos[35];
    sPedido pedidos;

    while(fgets(vecPedidos, 35, arch_pedidos))
    {
        if(desglosado(&pedidos, vecPedidos))
            printf("%d, %11s, %d\n", pedidos.nro_pedido, pedidos.cod_receta, pedidos.cantidad);

    }
}

void mostrar_archivo_recetas(FILE* arch_recetas)
{
    sReceta receta;
    fread(&receta, sizeof(sReceta), 1, arch_recetas);
    while(!feof(arch_recetas))
    {
        printf("%s, %s, %d\n", receta.cod_receta, receta.cod_ingr, receta.cantidad);
        fread(&receta, sizeof(sReceta), 1, arch_recetas);
    }
}
void mostrar_archivo_ingredientes(FILE* arch_ingredientes)
{
    sIngrediente ingredientes;
    fread(&ingredientes, sizeof(sIngrediente), 1, arch_ingredientes);
    while(!feof(arch_ingredientes))
    {
        printf("%s, %d\n", ingredientes.cod_ingr, ingredientes.stock);
        fread(&ingredientes, sizeof(sIngrediente), 1, arch_ingredientes);
    }
}



int desglosado(sPedido* pedido, char* vec)
{
    char* marcador;
    //////////Nro Pedido//////////
    if((marcador=strrchr(vec,'\t'))==NULL)
    {
        return 0;
    }
    sscanf(marcador+1,"%d",&(pedido->cantidad));
    *marcador='\0';
    /////////////Cod Receta/////////////////////
    if((marcador=strrchr(vec,'\t'))==NULL)
    {
        return 0;
    }
    strcpy(pedido->cod_receta,marcador+1);
    *marcador='\0';

    sscanf(vec,"%d",&(pedido->nro_pedido));

    return 1;
}

///////////////////////////PROCESO DATOS/////////////////////////////////////////////////////////////////////////////////////////////

///Procesa los pedidos del archivo Pedidos.txt, actualizando el archivo Ingredientes.dat, para que éste refleje la cantidad que queda en stock luego de despachar los pedidos.
//void satisfacer_pedidos(FILE* arch_pedidos, FILE* arch_recetas, FILE* arch_ingredientes, t_ind* vec_ind_rec, int ce_ind_rec, t_ind* vec_ind_ingr, int ce_ind_ingr)
//{
//	/Inserte el codigo acá ...
//}



/////Genera una cola con los ingredientes de la receta.
////int buscar_receta(FILE* arch_recetas, char* cod_receta, t_ind* vec_ind_rec, int ce_ind, t_cola* cola_rec_ingr)
//{
//	///Inserte el codigo acá ...
//}



/////Descuenta la cantidad indicada del ingrediente indicado, actualizando el archivo Ingredientes.dat.
////void descontar_stock_arch_ingr(FILE* arch_ingredientes, char* cod_ingr, int cant_a_descontar, t_ind* vec_ind_ingr, int ce_ind_ingr)
//{
//	///Inserte el codigo acá ...
//}
