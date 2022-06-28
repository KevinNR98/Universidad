/**//* 22.333.444-PEREZ_DEL_RIO,JuanManuel-(07-2299) *//**/

#include "Rectangulo.h"
#include "Figura.h"

Rectangulo::Rectangulo()
{
    this->lado1 = 0;
    this->lado2 = 0;
}


Rectangulo::Rectangulo(int lado1, int lado2)
{
    this->lado1 = lado1;
    this->lado2 = lado2;
}

int Rectangulo::area() const
{
    return (lado1)*(lado2);
}
