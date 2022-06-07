#include "Hora.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Hora::Hora()
{
    this->horas = 0;
    this->minutos = 0;
    this->segundos = 0;
}


Hora::Hora(int s)
{
    this->horas = s/3600;
    s %= 3600;
    this->minutos = s/60;
    this->segundos = s%60;
///ESTA FORMA ES OTRA POSIBILIDAD///
//    this->horas = s/3600;
//    this->minutos = ((s - this->horas*3600)/60);
//    this->segundos = s -(this->horas*3600+this->minutos*60);

}

//Hora::~Hora()
//{
//    //dtor
//}

Hora& Hora::operator =(const Hora& otra)
{
    this->horas = otra.horas;
    this->minutos = otra.minutos;
    this->segundos = otra.segundos;

    return *this;
}
Hora  Hora::operator ++()
{
    int totalSeg = 0;
    totalSeg += (this->segundos + 1) > 59? abs((this->segundos + 1)-60)*60 : (this->segundos + 1)*60;
    totalSeg += (this->minutos + 1) > 59? abs((this->minutos + 1)-59)*60 : (this->minutos + 1)*60;
    totalSeg += (this->horas + 1) > 23? abs((this->horas + 1)-23)*60 : (this->horas + 1)*60;

    return Hora(totalSeg);
}


Hora operator +(const Hora& h1, const Hora& h2)
{
  int totalSeg = 0;

  totalSeg += (h1.horas + h2.horas) > 23? abs((h1.horas + h2.horas)-23)*60 : (h1.horas + h2.horas)*60;
  totalSeg += (h1.minutos + h2.minutos) > 59? abs((h1.minutos + h2.minutos)-59)*60 : (h1.minutos + h2.minutos)*60;
  totalSeg += (h1.segundos + h2.segundos) > 59? abs((h1.segundos + h2.segundos)-60)*60 : (h1.segundos + h2.segundos)*60;


    return Hora(totalSeg);
}





ostream& operator <<(ostream& sal, const Hora& h)
{
    sal <<h.horas<<':'<<h.minutos<<':'<<h.segundos;
    return sal;
}
