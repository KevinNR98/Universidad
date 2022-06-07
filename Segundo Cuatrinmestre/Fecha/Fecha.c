#include <stdio.h>
#include "Fecha.h"
#include <string.h>
#include <ctype.h>

Fecha ingresarFecha()
{
    Fecha fecha;

    printf("Ingrese una fecha (D/M/A)--> ");
    scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);

    while(!esFechaValida(&fecha))
    {
        printf("La fecha ingresada es inv�lida. Ingr�sela nuevamente (D/M/A)--> ");
        scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);
    }
    return fecha;
}


boolean esFechaValida(const Fecha* f)
{
    return
        f->anio > 1600 &&
        f->mes >= 1 && f->mes <= 12 &&
        f->dia >= 1 && f->dia <= cantDiasMes(f->mes, f->anio);
}




boolean esBisiesto(int anio)
{
    return (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;
}


int cantDiasMes(int mes, int anio)
{
    static const int cdm[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(mes == 2 && esBisiesto(anio))
        return 29;

    return cdm[mes];
}


boolean hayMasDatos(const char* mensaje)
{
    char resp;
    printf("%s (s/n): ", mensaje);
    fflush(stdin);
    scanf("%c", &resp);
    resp = tolower(resp);

    while(resp != 's' && resp != 'n')
    {
        printf("Respuesta inv�lida. %s (s/n): ", mensaje);
        fflush(stdin);
        scanf("%c", &resp);
        resp = tolower(resp);
    }

    return resp == 's';
}


//incremento en meses
Fecha sumarDiasAFecha(const Fecha* fecha, int dias)
{
    Fecha fSuma = *fecha;
    fSuma.dia += dias;
    int cdm;

    while(fSuma.dia > (cdm = cantDiasMes(fSuma.mes, fSuma.anio)))
    {
        fSuma.dia -= cdm;
        fSuma.mes++;

        if(fSuma.mes > 12)
        {
            fSuma.mes = 1;
            fSuma.anio++;
        }
    }
    return fSuma;
}


//incremento en anios, me olvido que el anio tiene meses y semanas
//Fecha sumarDiasAFechaV2(const Fecha* fecha, int dias)
//{
//
//}

int difenDiasEntreFechas(const Fecha* f1, const Fecha* f2)
{
    int dif=diaDelAnio(f2) - diaDelAnio(f1);

    int anioAct =f1->anio;
    while(anioAct<f2->anio)
    {
        dif +=cantDiasAnio(anioAct);
        anioAct++;
    }
    return dif;
}


int diaDelAnio(const Fecha* fecha)
{
    int mesAct = 1;
    int diaAnio = fecha->dia;

    while(mesAct < fecha->mes)
    {
        diaAnio += cantDiasMes(mesAct, fecha->anio);
        mesAct++;
    }
    return diaAnio;
}


char menuFechas()
{
    char opc;
    imprimirMenu(falso);

    fflush(stdin);
    scanf("%c", &opc);
    opc = toupper(opc);
    while(opc != 'M' && opc != 'S' && opc != 'D' && opc != 'A' && opc != 'X')
    {
        fflush(stdin);
        scanf("%c", &opc);
        opc = toupper(opc);
        imprimirMenu(verdadero);
    }
    return opc;
}

void imprimirMenu(boolean error)
{
    //system("cls");
    printf ("***** Fechas ******\n");
    printf("=====================\n\n");

    printf ("**** Menu ****\n");
    printf("M - Mostrar Fecha\n");
    printf("S - sumar Dias\n");
    printf("D - diferencia en Dias\n");
    printf("A -  Dia del Anio\n\n");
    printf ("X - Salir \n\n");
    printf("Ingrese su opcion --> ");
    printf(error? "opcion erronea, ingresela nuevamente --> ":"ingrese su opcion: ");
}


void opcionSumarDias(Fecha* fechaInicial)
{
    int dias = ingresarEnteroPositivo("Ingrese los dias a sumar");
    *fechaInicial = sumarDiasAFecha(fechaInicial,dias);
    printf("La fecha suma es: %d/%d/%d\n",fechaInicial->dia,fechaInicial->mes,fechaInicial->anio);
    pausa();
}

void opcionDiferenciaEnDias(Fecha* fechaInicial)
{
    Fecha f2= ingresarFecha();
    int dif=difenDiasEntreFechas(fechaInicial,&f2);
    printf("La diferencia es de %d dias.\n",dif);
    pausa();
}

void opcionDiaDelAnio(Fecha* fechaInicial)
{
    int diaAnio= diaDelAnio(fechaInicial);
    printf("El dia del anio es: %d\n", diaAnio);
    pausa();
}


int ingresarEnteroPositivo(const char* mensaje)
{
    int entero;
    printf("%s --> ", mensaje);
    fflush(stdin);
    scanf("%d", &entero);

    while(entero < 1)
    {
        printf("Error: Debe ingresar un entero positivo --> ");
        fflush(stdin);
        scanf("%d", &entero);
    }
    return entero;
}


void opcionMostrarFecha(const Fecha* fechaInicial)
{
    printf("La fecha inicial es: %d/%d/%d\n",fechaInicial->dia,fechaInicial->mes,fechaInicial->anio);
    pausa();
}

int cantDiasAnio(int anio)
{
    return esBisiesto(anio)?366:365;
}


void pausa()
{
    printf("presione una tecla para continuar. ");
    fflush(stdin);
}

