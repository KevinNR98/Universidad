#ifndef HORA_H
#define HORA_H

#include <iostream>

using namespace std;

class Hora
{
    private:
        int horas;
        int minutos;
        int segundos;

    public:
        Hora();
        Hora(int s);
//        ~Hora();

        Hora& operator =(const Hora& otra);
        Hora operator ++();

        friend Hora operator +(const Hora& h1, const Hora& h2);
        friend ostream& operator <<(ostream& sal, const Hora& h);
};



#endif // HORA_H
