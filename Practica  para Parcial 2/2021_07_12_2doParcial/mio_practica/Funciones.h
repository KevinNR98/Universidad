#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#define ARCH_COMP_DAT "Componentes.dat"
#define ARCH_COMP_IDX "Componentes.idx"
#define ARCH_AYR_DAT  "ArmadosYReparaciones.dat"
#include "Arbol.h"
#include "ListaDoble.h"

typedef struct
{
    char codigo[21];
    char descripcion[51];
    int stock;
    double precioUnitario;
}tComponente;


typedef struct
{
    int nroOp;
    char codigo[21];
    int cantidad;
    double precioUnitario;
}tArmadoYRep;


typedef struct
{
    char codigo[21];
    int nroReg;
}tIndComponente;



int compararIndice(const void* a, const void* b);

void mostrarIndice(const void* a);

int acumuladorCantidad(void** info, unsigned* tam, const void* dato, unsigned cantBytes);

void mostrarIndiceArch();

void mostrarLista(const void* a);

int compararCodigo(const void* a, const void* b);


#endif // FUNCIONES_H_INCLUDED
