#include "horadeldia.h"
#include <iostream>

using namespace std;

HoraDelDia::HoraDelDia(int horas,int minutos,int segundos)
{
    this->horas=horas%24;
    this->minutos=minutos%60;
    this->segundos=segundos&60;
}

ostream& operator<<(ostream&salida,const HoraDelDia &obj)
{
    salida<<"Hora: "<<obj.horas<<"Minutos: "<<obj.minutos<<"Segundos: "<<obj.segundos;
    return salida;
}

istream& operator>>(istream&entrada,const HoraDelDia &obj)
{
    char aux=':';
    int aux;
    entrada>>obj.horas>>obj.minutos>>obj.segundos;
    return entrada;
}

bool HoraDelDia::operator>=(const HoraDelDia&obj)
{
    if(this->horas>=obj.horas)
        if(this->minutos>=obj.minutos)
            if(this->segundos>=obj.segundos)
                return true;
    return false;
}

bool HoraDelDia::operator<(const HoraDelDia&obj)
{
    if(this->horas<obj.horas)
    {
        if(this->minutos<obj.minutos)
        {
            if(this->segundos<obj.segundos)
            {
                return true;
            }
        }
    }
    return false;
}

HoraDelDia HoraDelDia::operator++(int)
{
    HoraDelDia result=(*this);
    this->segundos=this->segundos+1;
    return result;
}

HoraDelDia HoraDelDia::operator+(const HoraDelDia&obj)
{
    int acumMin=0,acumSeg=0;
    HoraDelDia result=(*this);
    acumMin=(this->minutos+obj.minutos)/60;
    acumSeg=(this->segundos+obj.segundos)/60;
    result.horas=(this->horas+obj.horas+acumMin)%24;
    result.minutos=(this->minutos+obj.minutos+acumSeg)%60;
    result.segundos=(this->segundos+obj.segundos)%60;
    return result;
}

HoraDelDia& HoraDelDia::operator+=(int segundos)
{
    int acumSeg=0,acumMin=0;
    acumSeg=(this->segundos+segundos)/60;
    acumMin=(this->minutos+acumSeg)/60;
    this->segundos=(this->segundos+segundos)%60;
    this->minutos=(this->minutos+acumSeg)%60;
    this->horas=(this->horas+acumMin)%24;

    return (*this);
}

HoraDelDia& operator+(int segundos, HoraDelDia &obj)
{
    int acumSeg=0,acumMin=0;
    acumSeg=(obj.segundos+segundos)/60;
    acumMin=(obj.minutos+acumSeg)/60;
    obj.segundos=(obj.segundos+segundos)%60;
    obj.minutos=(obj.minutos+acumSeg)%60;
    obj.horas=(obj.horas+acumMin)%24;
    return obj;
}
