/**//* 22.333.444-PEREZ_DEL_RIO,JuanManuel-(07-2299) *//**/
#include <math.h>
#include "Cuadrado.h"
#include "Figura.h"
#include "FiguraInvalidaException.h"

Cuadrado::Cuadrado()
{
    this->lado1 = 0;
}


Cuadrado::Cuadrado(int lado1)
{
    if(lado1 == 0)
        throw FiguraInvalidaException();

    this->lado1 = lado1;
}


int Cuadrado::area() const
{
    return (lado1)*(lado1);
}
