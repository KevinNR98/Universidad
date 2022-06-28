#ifndef RECTA_H
#define RECTA_H
#include "Punto.h"

class Recta :
{
private:
    Punto r1;
    Punto r2;

    public:
        Recta(const Punto& r1, const Punto& r2);
        friend Recta operator -(const Recta& r1, const Punto& p);
};

#endif // RECTA_H
