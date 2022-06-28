#include <stdio.h>
#include <stdlib.h>

char* strcat_reverso(char* cad1, const char* cad2);

int main()
{
    char cad[] = "mundo!";
    char cad2[] = "Hola ";

    printf("%s\n", strcat_reverso(cad, cad2));

    return 0;
}


char* strcat_reverso(char* cad1, const char* cad2)
{
    int longCad2 = mi_strlen(cad2);
    char* ini = cad1;
    char* fin = (mi_strlen(cad1) + ini);

    while(fin >= ini)
    {
        cad1 = longCad2 + fin;
        *cad1 = *fin;
        fin--;
    }
    cad1 = ini;
    while(*cad2)
    {
        *cad1 = *cad2;
        cad1++;
        cad2++;
    }
    return ini;

}


int mi_strlen(const char* cad)
{
    int cont = 0;
    while(*cad)
    {
        cad++;
        cont++;
    }
    return cont;
}
