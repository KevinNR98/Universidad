#ifndef CADENA_H_INCLUDED
#define CADENA_H_INCLUDED
#include <ctype.h>
#include <stddef.h>
#include "../Comun/Comun.h"

typedef struct
{
    char* cursor;
    boolean finSecuencia;
}SecuenciaPalabras;


typedef struct
{
    char* ini;///Un vector seria una opcion pero seria mas lento, por que si tengo que modificar la palabra seria un problema, la dimension del vector seria otro problema.
    char* fin;
}Palabra;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
size_t miStrlen(const char* cad);

char* miStrStr(char* cad, const char* subCad);

int miStrcmp(const char* s1, const char* s2);

char* miStrcpy(char* s1, const char* s2);

char* miStrcat(char* s1, const char* s2);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* normalizar(const char* origen, char* destino);

void crearSecuencia(SecuenciaPalabras* sec,  char* cad);

boolean finSecuenciaPalabras(const SecuenciaPalabras* sec);

void leerPalabra(SecuenciaPalabras* sec, Palabra* pal);

void formatearPalabra(Palabra* pal);

void escribirCaracter(SecuenciaPalabras* sec, char caracter);

void reposicionarSecuencia(SecuenciaPalabras* sec, int despl);

void escribirPalabra(SecuenciaPalabras* sec, const Palabra* pal, Palabra* palDest);

boolean esLetra(char c);

char aMayuscula(char c);

char aMinuscula(char c);

void cerrarSecuencia(SecuenciaPalabras* sec);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // CADENA_H_INCLUDED
