#ifndef DELIVERYRESUELTO_H_INCLUDED
#define DELIVERYRESUELTO_H_INCLUDED
#include <E:\Universidad\Programacion\Practica para Parcial 1\Resueltos\ParcialDeliveryResuelto\TiposDelivery.h>
#include <E:\Universidad\Programacion\Practica para Parcial 1\Resueltos\ParcialDeliveryResuelto\indice_string.h>
#include <E:\Universidad\Programacion\Practica para Parcial 1\Resueltos\ParcialDeliveryResuelto\Cola.h>


#define DUPLICADO 2
#define SIN_MEM 1
#define TODO_OK 0
#define COLA_LLENA 0

#define TAM 500

#define VERDADERO 1
#define FALSO 0

#define ERROR_ARCHIVO 3

#define NO_EXISTE 4

typedef int booleano;

void mostrar_archivo_pedidos(FILE* arch_pedidos);
void mostrar_archivo_recetas(FILE* arch_recetas);
void mostrar_archivo_ingredientes(FILE* arch_ingredientes);
int desglosado(sPedido* pedido, char* vec);

///Procesa los pedidos del archivo Pedidos.txt, actualizando el archivo Ingredientes.dat, para que éste refleje la cantidad que queda en stock luego de despachar los pedidos.
//void satisfacer_pedidos(FILE* arch_pedidos, FILE* arch_recetas, FILE* arch_ingredientes, t_ind* vec_ind_rec, int ce_ind_rec, t_ind* vec_ind_ingr, int ce_ind_ingr);

///Genera una cola con los ingredientes de la receta.
//int buscar_receta(FILE* arch_recetas, char* cod_receta, t_ind* vec_ind_rec, int ce_ind, t_cola* cola_rec_ingr);

///Descuenta la cantidad indicada del ingrediente indicado, actualizando el archivo Ingredientes.dat.
//void descontar_stock_arch_ingr(FILE* arch_ingredientes, char* cod_ingr, int cant_a_descontar, t_ind* vec_ind_ingr, int ce_ind_ingr);

#endif // DELIVERYRESUELTO_H_INCLUDED
