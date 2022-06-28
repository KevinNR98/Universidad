#include <stdio.h>
#include <stdlib.h>
#define ESMAYUS(X) ((X) = 'A')

char* mi_strstr(const char*, const char*);

int main()
{
    char cad[] = "Hola a todos";
    char cad2[] = "la";
    printf("Mi_strstr = %s\n", mi_strstr(cad, cad2));
    printf( "strstr = %s\n", strstr( cad, cad2 ));


    return 0;
}


char* mi_strstr(const char* cadena, const char* subcadena)
{
    char* pCad = cadena;
    char* pSub = subcadena;

    while(*pCad && *pSub)
    {
        if(*pCad == *pSub)
        {
            return pCad;
        }
        pCad++;
    }
    if(*pSub == '\0')
        return cadena;
    return NULL;
}
