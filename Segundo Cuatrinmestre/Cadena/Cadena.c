#include "Cadena.h"
#include <string.h>


size_t miStrlen(const char* cad)////Cuenta el nro de caracteres de un string.
{
    const char* i = cad;

    while(*i != '\0')
        i++;

    return i - cad;
}


char* miStrStr(char* cad, const char* subCad)///Busca una subcadena dentro de una cadena.
{
    char*i = cad, *encontrada;
    const char* j; ///tiene que ser const por que si no podria modificar la cadena a la que apunta. j no seria const sino la cadena a la que apunta.

    if(!*subCad)///(miStrlen(subCad) == 0), (*subCad == '\0')
        return cad;

    while(*i)///(*i != '\0') mientras haya un caracter.
    {
        while(*i && *i != *subCad)
            i++;

        if(*i)
        {
            encontrada = i;
            i++;
            j = subCad + 1;

            while(*i && *j && *i == *j)
            {
                i++;
                j++;
            }

            if(!*j) ///(*j == '\0')
                return encontrada;
            else
                i = encontrada + 1;///evita el solapamiento al buscar la subcadena ej: lalalo buscando lalo.
        }
    }
    return NULL;
}

int miStrcmp(const char* s1, const char* s2)////Compara la cadena apuntada por s1 con la cadena apuntada por s2.
{
    while(*s1 && *s2)
    {
        s1++;
        s2++;
    }
    return *s1 - *s2;///La función retorna un número entero mayor, igual, o menor que cero, dependiendo de si s1>s2,s1==s2 o s1<s2.
}

char* miStrcpy(char* s1, const char* s2)///Copia la cadena apuntada por s2(origen) (incluyendo el carácter nulo) a la cadena apuntada por s1(destino).
{
    char* iniS1 = s1;

    while(*s2)
    {
        *s1 = *s2;
        s1++;
        s2++;
    }
    *s1 = '\0';
    return iniS1;
}

char* miStrcat(char* s1, const char* s2)///Añade una copia de la cadena apuntada por s2 (incluyendo el carácter nulo) al final dela cadena apuntada por s1.
{                                       ///El carácter inicial de s2 sobrescribe el carácter nulo al finalde s1.
    char* iniS1;

    iniS1 = s1;
    s1 = s1 + miStrlen(s1);

    while(*s2)
    {
        *s1 = *s2;
        s1++;
        s2++;
    }
    *s1 = '\0';
    return iniS1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* normalizar(const char* origen, char* destino)
{
    SecuenciaPalabras secLec;/// de lectura
    SecuenciaPalabras secEscr;/// de escritura
    Palabra pal, palDest;

    crearSecuencia(&secLec, (char*)origen);///lec
    crearSecuencia(&secLec, destino);///escr

    leerPalabra(&secLec, &pal);
    while(!finSecuenciaPalabras(&secLec))
    {
        escribirPalabra(&secEscr, &pal, &palDest);
        formatearPalabra(&palDest);///pone mayus o minus
        escribirCaracter(&secEscr, ' ');///*(secEscr->cursor) = '\0', es un problema por que va poner un espacio al final del texto
        leerPalabra(&secLec, &pal);
    }

    reposicionarSecuencia(&secEscr, -1); ///solucional el espacio de mas que ponel el escribirCaracter
    cerrarSecuencia(&secEscr);

    return destino;
}



void crearSecuencia(SecuenciaPalabras* sec,  char* cad)
{
    sec->cursor = cad;
    sec->finSecuencia = falso;
}

void leerPalabra(SecuenciaPalabras* sec, Palabra* pal)
{
    char* act = sec->cursor;/// para que sea mas eficiente y no usar la desrefencia constantemente me manejo con act

    while(*act && !esLetra(*act))
        act++;

    if(!*act)
    {
        sec->cursor = act;
        sec->finSecuencia = verdadero;
        return;
    }


    pal->ini = act;/// direccion del primer caracter de la  palabra que encontro.

    while(*act && esLetra(*act))
        act++;

    pal->fin = act - 1;/// se posiciona en la direccion del ultimo caracter de la palabra

    sec->cursor = act;///muevo el cursor para leer la proxima palabra.
}


boolean finSecuenciaPalabras(const SecuenciaPalabras* sec)
{
    return sec->finSecuencia;/// desrreferencio el puntero, retorna verdadero cuando llega al fin y falso cuando apunte al \0, cuando no hay un caracter es fin de la secuencia
}


void escribirPalabra(SecuenciaPalabras* sec, const Palabra* pal, Palabra* palDest)
{
    palDest->ini = sec->cursor;
    char* actDest = sec->cursor;


    for(char* actOrig = pal->ini; actOrig <= pal->fin; actOrig++, actDest++)///copio caracter a caracter
    {
        *actDest = *actOrig;
    }


    palDest->fin = actDest - 1;

    sec->cursor = actDest;
}


void formatearPalabra(Palabra* pal)
{
    *(pal->ini) = aMayuscula(*(pal->ini));

    for(char* act = pal->ini + 1; act <= pal->fin; act++)
        *act = aMinuscula(*act);
}

void escribirCaracter(SecuenciaPalabras* sec, char caracter)
{
    *(sec->cursor) = caracter;
    sec->cursor++;
}

boolean esLetra(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

char aMayuscula(char c)
{
    return c >= 'a' && c <= 'z'? c - ('a' - 'A') : c;
}

char aMinuscula(char c)
{
    return c >= 'A' && c <= 'Z'? c + ('a' - 'A') : c;
}

void reposicionarSecuencia(SecuenciaPalabras* sec, int despl)///validar si no esta fuera del vector etc.
{
    sec->cursor += despl;
}

void cerrarSecuencia(SecuenciaPalabras* sec)
{
    *(sec->cursor) = '\0';
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
