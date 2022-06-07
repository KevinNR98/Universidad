#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\Cadena\Cadena.h"



int main()
{
    char cad[] = "Hola";
    char subCad[] = "lalalo";
    char cadANormalizar[] = "%%&hOlA";
    int val;

    char* res = miStrStr(cad, subCad);

    if(res)/// (res != NULL)
        printf("Cadena encontrada: %s\n", res);
    else
        printf("Cadena no encontrada\n");

        val = miStrcmp(cad, subCad);

        if(val == 0)
            printf("Las cadenas son iguales.\n");
        else if(val < 0)
            printf("La cadena s1 es menor que la cadena s2.\n");
        else
            printf("La cadena s1 es mayor que la cadena s2.\n");


        miStrcpy(subCad, cad);
        printf("La cadena modificada quedo: %s.\n", subCad);



        printf("La cadena s1 concatenada con s2 queda: %s", cad, subCad, miStrcat(cad, subCad));
    printf("La cadena %s tiene %d caracteres\n", cad, miStrlen(cad));



    printf("La cadena normalizada: %s\n", normalizar(cadANormalizar, cadANormalizar));




    return 0;
}
