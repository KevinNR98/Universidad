#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED
#include "../Comun/Comun.h"

typedef struct
{
    int dia;
    int mes;
    int anio;
}Fecha;



Fecha ingresarFecha();

boolean esFechaValida(const Fecha* f);

int cantDiasMes(int mes, int anio);

boolean esBisiesto(int anio);

boolean hayMasDatos();

Fecha sumarDiasAFecha(const Fecha* fecha, int dias);

Fecha restarDiasAFecha(const Fecha* fecha, int dias);

int difDiasEntreFechas(const Fecha* f1, const Fecha* f2);

int diasSemana(const Fecha* fecha);

int diaDelAnio(const Fecha* fecha);

Fecha sumarDiasAFechaV2(const Fecha* fecha, int dias);

char menuFechas();

void imprimirMenu(boolean error);

void opcionSumarDias(Fecha* fechaInicial);

void opcionDiferenciaEnDias(Fecha* fechaInicial);

void opcionDiaDelAnio(Fecha* fechaInicial);

void opcionMostrarFecha(const Fecha* fechaInicial);

void pausa();

int ingresarEnteroPositivo(const char* mensaje);

int cantDiasAnio(int anio);



#endif // FECHA_H_INCLUDED
