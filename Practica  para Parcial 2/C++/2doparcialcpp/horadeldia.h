#ifndef HORADELDIA_H
#define HORADELDIA_H
#include <iostream>

using namespace std;

class HoraDelDia
{
private:
    int horas;
    int minutos;
    int segundos;
public:
    HoraDelDia(int horas=0,int minutos=0,int segundos=0);
    friend ostream& operator<<(ostream&salida,const HoraDelDia &obj);
    friend istream& operator>>(istream&entrada,const HoraDelDia &obj);
    bool operator>=(const HoraDelDia&obj);
    bool operator<(const HoraDelDia&obj);
    HoraDelDia operator++(int);
    HoraDelDia operator+(const HoraDelDia&obj);
    HoraDelDia& operator+=(int segundos);
//    friend HoraDelDia& operator+(int segundos,HoraDelDia &obj);
    friend HoraDelDia& operator+(int segundos,HoraDelDia &obj);
//    HoraDelDia& operator++();
};
#endif // HORADELDIA_H
