#ifndef CADENA_H
#define CADENA_H

#include <iostream>

using namespace std;

class Cadena
{
    private:
        char* cad;
        Cadena(char *);

    public:
        Cadena();
        Cadena(const char *);
        Cadena(const Cadena& );
        int longitud();

        Cadena& operator =(const Cadena& otra);
        friend Cadena operator +(const Cadena& cad1, const Cadena& cad2);
        friend ostream& operator <<(ostream& sal, const Cadena& cad);
        friend istream& operator >>(istream& ent, Cadena& cad);
};





#endif // CADENA_H
