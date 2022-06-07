#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Funciones.h"

void suma(char* cad1, char* cad2)
{
    int num1, num2, sum, rest = 0, carry, rta;
    tPila* pila1, *pila2, *pilaR;
    crearPila(&pila1);
    crearPila(&pila2);
    crearPila(&pilaR);


    while(*cad1)
    {
        num1 = *cad1 - '0';
        ponerEnPila(&pila1, &num1, sizeof(num1));
        cad1++;
    }
    while(*cad2)
    {
        num2 = *cad2 - '0';
        ponerEnPila(&pila2, &num2, sizeof(num2));
        cad2++;
    }

    while(!pilaVacia(&pila1) && !pilaVacia(&pila2))
    {
        sacarDePila(&pila1, &num1, sizeof(int));
        sacarDePila(&pila2, &num2, sizeof(int));

        sum = num1 + num2 + carry;
        carry = 0;
        if(sum >= 10)
        {
            carry = 1;
            rest = sum%10;
            ponerEnPila(&pilaR, &rest, sizeof(int));
        }
        else
        {
            ponerEnPila(&pilaR, &sum, sizeof(int));
        }

    }

    while(!pilaVacia(&pila1))
    {
        sacarDePila(&pila1, &num1, sizeof(int));

        sum = num1 + carry;
        carry = 0;
        if(sum >= 10)
        {
            carry = 1;
            rest = sum%10;
            ponerEnPila(&pilaR, &rest, sizeof(int));
        }
        else
        {
            ponerEnPila(&pilaR, &sum, sizeof(int));
        }
    }

    while(!pilaVacia(&pila2))
    {
        sacarDePila(&pila2, &num2, sizeof(int));

        sum = num2 + carry;
        carry = 0;
        if(sum >= 10)
        {
            carry = 1;
            rest = sum%10;
            ponerEnPila(&pilaR, &rest, sizeof(int));
        }
        else
        {
            ponerEnPila(&pilaR, &sum, sizeof(int));
        }
    }

    if(carry != 0)
    {
        ponerEnPila(&pilaR, &carry, sizeof(int));
    }


    printf("La suma da: ");
    while(!pilaVacia(&pilaR))
    {
        sacarDePila(&pilaR, &rta, sizeof(int));
        printf("%d", rta);
    }
}


int main()
{
    char cad[] = {"9874567"};
    char cad1[] = {"1234566"};

    suma(cad, cad1);
}
