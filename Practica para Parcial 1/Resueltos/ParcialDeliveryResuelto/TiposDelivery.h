#ifndef TIPOSDELIVERY_H_INCLUDED
#define TIPOSDELIVERY_H_INCLUDED

typedef struct
{
    int nro_pedido;
    char cod_receta[11];
    int cantidad;
} sPedido;

typedef struct
{
    char cod_receta[11];
    char cod_ingr[11];
    int cantidad;
} sReceta;


typedef struct
{
    char cod_ingr[11];
    int stock;
} sIngrediente;

#endif // TIPOSDELIVERY_H_INCLUDED
