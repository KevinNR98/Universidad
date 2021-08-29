#ifndef MIFUNCION_H_INCLUDED
#define MIFUNCION_H_INCLUDED
#include "tipos.h"
#define TAM_FECHA_HORA 12
#define TAM_DOMINIO 10
#define TAM_SENTIDO 1
#define TAM_SECTOR 1
#define TAM_LINEA 24


int crearLotePrueba_mio(const char* filename);
int generarInforme_mio(const char* filename, const char* output, const tsector* secs);

void accion(const void*a);
int comparar(const void* cmp1, const void* cmp2);
int acumuladorErrores(void** info, unsigned* tam, const void* dato, unsigned cantBytes);

#endif // MIFUNCION_H_INCLUDED
