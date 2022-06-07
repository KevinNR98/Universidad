#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TDA_PILA_IMP_DINAMICA///TDA_PILA_IMPL_ESTATICA

#include "../TDAPila/TDAPila.h"

#define ERR_MEMORIA 1

#define aBin(c) ((c) - '0')
#define aChar(e) ((e) + '0')

boolean cargarPila(Pila* pila, int cantCeros, const char* vec);
void cargarVector(char* vec, Pila* pila);


int main(int argc, char* argv[])
{
    Pila pilaN1, pilaN2, pilaSuma;

    int cantCeros = strlen(argv[1]) - strlen(argv[2]);///calcula la cant de ceros que voy a poner en la pila
    char d1, d2, dS;///digitos
    int acarreo = 0, sumaD;
    int tamSuma = 0;
    char* sumaS;///donde voy a guardar la pilaSuma
    char acarreoC = '1';


    crearPila(&pilaN1);
    crearPila(&pilaN2);
    crearPila(&pilaSuma);


    cargarPila(&pilaN1, cantCeros < 0? -cantCeros : 0, argv[1]);///el ternario es para paserle cuantos ceros le tengo que poner al numero para poder sumarlo
    cargarPila(&pilaN2, cantCeros > 0? cantCeros : 0, argv[2]);


    while(!pilaVacia(&pilaN1))
    {
        desapilar(&pilaN1, &d1, sizeof(char));
        desapilar(&pilaN2, &d2, sizeof(char));

        sumaD = aBin(d1) + aBin(d2) + acarreo;

        acarreo = sumaD / 10;
        dS = aChar(sumaD % 10);

        apilar(&pilaSuma, &dS, sizeof(char));
        tamSuma++;
    }


    if(acarreo == 1)
    {
        apilar(&pilaSuma, &acarreoC, sizeof(char));
        tamSuma++;
    }

    sumaS = (char*)malloc(tamSuma);
    if(!sumaS)
    {
        puts("!No hay memoria.");
        return ERR_MEMORIA;
    }



    cargarVector(sumaS, &pilaSuma);

    puts(sumaS);

    free(sumaS);

    return 0;
}


boolean cargarPila(Pila* pila, int cantCeros, const char* vec)
{
    const char* act = vec;
    boolean apilo = verdadero;
    char ceroC = '0';

    for(int i = 0; i < cantCeros && apilo; i++)
        apilo = apilar(pila, &ceroC, sizeof(char));

    while(apilo && *act)
    {
        apilo = apilar(pila, act, sizeof(char));
        act++;
    }

    return apilo;
}



void cargarVector(char* vec, Pila* pila)
{
    char* act = vec;

    while(!pilaVacia(pila))
    {
        desapilar(pila, act, sizeof(char));
        act++;
    }

    *act = '\0';
}
