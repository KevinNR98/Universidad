#include <stdlib.h>
#include <cmath>
#include "Recta.h"
#include "Punto.h"

Recta::Recta(const Punto& r1, const Punto& r2)
: r1(r1), r2(r2)
{}


Recta operator -(const Recta& r1, const Punto& p)
{
    double temp;

    temp = abs((r1.r2.ejeY-r1.r1.ejeY)*p.ejeX -(r1.r2.ejeX-r1.r1.ejeX)*p.ejeY)/sqrt(pow(r1.r2.ejeY-r1.r1.ejeY)+ pow(r1.r2.ejeX-r1.r1.ejeX));

    return temp;
}
