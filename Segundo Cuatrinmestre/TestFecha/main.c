#include <stdio.h>
#include <stdlib.h>
#include "../Fecha/Fecha.h"

int main()
{
    Fecha fecha;

    do
    {
        printf("Ingrese una fecha (D/M/A)--> ");
        scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);
        while (!esFechaValida(&fecha))
        {
            printf("La fecha ingresada es invalida. Ingrese nuevamente (D/M/A)--> ");
            fflush(stdin);
            scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);
        }
    }while(hayMasDatos("Desea ingresar otra fecha?"));



    return 0;
}
