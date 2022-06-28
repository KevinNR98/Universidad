/**//* 22.333.444-PEREZ_DEL_RIO,JuanManuel-(07-2299) *//**/

#ifndef RECTANGULO_H_
#define RECTANGULO_H_
#include "Figura.h"

class Rectangulo : public Figura
{
private:
    int lado1;
    int lado2;

public:
    Rectangulo();
    Rectangulo(int lado1, int lado2);

    int area() const;
};






#endif // RECTANGULO_H_
