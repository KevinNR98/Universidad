/**//* 22.333.444-PEREZ_DEL_RIO,JuanManuel-(07-2299) *//**/

#ifndef CUADRADO_H_
#define CUADRADO_H_

#include "Figura.h"

class Cuadrado : public Figura
{
private:
    int lado1;

public:
    Cuadrado();
    Cuadrado(int lado1);

    int area() const;

};






#endif // CUADRADO_H_
