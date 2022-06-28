#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "menu.h"

void pausa(char *msj){
    if (*msj)
        printf("\n%s",msj);
    puts("\nPresione enter para continuar...");
    fflush(stdin);
    scanf("%*c");
}
char pedir_opcion(const char m[][TAM_MENU], const char *tit, const char *msj){
    char op;
    int i;
    //No es crossplatform
    //system("CLS");
    printf("\n\n %s \n", tit);
    for ( i=1 ; i <= strlen(m[0]) ; i++)
        printf("\n %c - %s", m[0][i-1], m[i]);
    printf("\n\n%s: ", msj);
    fflush(stdin);
    scanf("%c", &op);
    return toupper(op);
}

char menu(const char m[][TAM_MENU], const char *tit){
    char op;
    op = pedir_opcion(m, tit, "Ingrese opcion: ");
    while(!strchr(m[0], op))
        op = pedir_opcion(m, tit, "Opcion erronea. Ingrese nuevamente: ");
    return op;
}
