/**//* 22.333.444-PEREZ_DEL_RIO,JuanManuel-(07-2299) *//**/

#ifndef TRIANGULO_H_
#define TRIANGULO_H_
#include "Figura.h"


class Triangulo : public Figura
{
private:
    int lado1;
    int lado2;

public:
    Triangulo();
    Triangulo(int lado1, int lado2);

    int area() const;
};






#endif // TRIANGULO_H_
