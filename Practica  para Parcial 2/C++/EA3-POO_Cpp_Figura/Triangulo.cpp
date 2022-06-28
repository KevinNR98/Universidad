/**//* 22.333.444-PEREZ_DEL_RIO,JuanManuel-(07-2299) *//**/

#include "Triangulo.h"
#include "Figura.h"
#include "FiguraInvalidaException.h"


Triangulo::Triangulo()
{
    this->lado1 = 0;
    this->lado2 = 0;
}


Triangulo::Triangulo(int lado1, int lado2)
{
    if(lado1 < 0 && lado2 < 0)
        throw FiguraInvalidaException();

    this->lado1 = lado1;
    this->lado2 = lado2;
}

int Triangulo::area() const
{
    return (lado1)*(lado2)/2;
}
