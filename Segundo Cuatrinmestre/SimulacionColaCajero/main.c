#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TDA_COLA_IMPL_DINAMICA
#include "../TDACola/TDACola.h"

typedef struct
{
    char nombre[9];
    int tiempoDemora;
} Cliente;


int calcularTiempoDeArribo();
int calcularTiempoDemora();
const char* obtenerNombreRandom();


int main()
{
    int contVecesColaVacia = 5;
    int contTiempoArribo = calcularTiempoDeArribo();
    int contMinutos = 0;
    Cliente cli;
    Cliente cliEnCajero;
    boolean cajeroOcupado = falso;

    srand(time(NULL));

    Cola colaCajero;
    crearCola(&colaCajero);


    while(contVecesColaVacia > 0)
    {
        printf("Minuto %d.\n", contMinutos);

        if(contTiempoArribo == 0)
        {
            strcpy(cli.nombre, obtenerNombreRandom());
            cli.tiempoDemora = calcularTiempoDeArribo();
            if(cajeroOcupado)
                encolar(&colaCajero, &cli, sizeof(Cliente));
            else
            {
                cliEnCajero = cli;
                cajeroOcupado = verdadero;
            }

            printf("%s llego. Va a demorar %d minutos.\n", cli.nombre, cli.tiempoDemora);
            contTiempoArribo = calcularTiempoDeArribo();

        }

        if(cajeroOcupado && cliEnCajero.tiempoDemora == 0)
        {
            printf("%s salió del cajero.\n", cliEnCajero.nombre);
            cajeroOcupado = falso;
        }



        if(!cajeroOcupado && !colaVacia(&colaCajero))
        {
            desencolar(&colaCajero, &cliEnCajero, sizeof(Cliente));
            cajeroOcupado = verdadero;
            printf("%s entró al cajero. Va a demorar %d minutos.\n", cliEnCajero.nombre, cliEnCajero.tiempoDemora);

            if(colaVacia(&colaCajero))
                contVecesColaVacia--;
        }

        contTiempoArribo--;

        if(cajeroOcupado)
            cliEnCajero.tiempoDemora--;

        contMinutos++;
    }

    return 0;
}



int calcularTiempoDeArribo()
{
    static const int tiemposArribo[] = {1, 5, 9};
    int random = rand() % 3;/// me va a dar valores entre 0 y 2

    return tiemposArribo[random];
}


int calcularTiempoDemora()
{
    static const int tiemposDemora[] = {1, 3, 5};
    int random = rand() % 3;/// me va a dar valores entre 0 y 2

    return tiemposDemora[random];
}

const char* obtenerNombreRandom()
{
    static const char nombres[][9]= {"Jose", "Pedro", "Luis", "Agustin", "Bernardo", "Carlos", "Dario", "Esteban", "Fabio", "Maria", "Julieta", "Romina", "Natalia", "Andrea"};

    return nombres[rand() % 14];
}
