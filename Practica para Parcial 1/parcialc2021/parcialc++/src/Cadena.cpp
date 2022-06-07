#include <string.h>
#include "Cadena.h"

///CONSTRUCTORES
Cadena::Cadena()
{
    this->cad = new char[1];
    this->cad[0] = '\0';
}

Cadena::Cadena(const char * cad)
{
    this->cad = new char[strlen(cad) + 1];
    strcpy(this->cad,cad);
}

Cadena::Cadena(const Cadena& otra)
{
    this->cad = new char[strlen(otra.cad) + 1];
    strcpy(this->cad,otra.cad);
}

int Cadena::longitud()
{
    return strlen(this->cad);
}


///CONSTRUCTOR PRIVADO
Cadena::Cadena(char * cad)
{
    this->cad = cad;
}




Cadena& Cadena::operator =(const Cadena& otra)
{
    if(strlen(this->cad) != strlen(otra.cad))
    {
        delete [] this->cad;
        this->cad = new char[strlen(otra.cad) + 1];
    }

    strcpy(this->cad,otra.cad);
    return *this;
}

Cadena operator + (const Cadena& cad1, const Cadena& cad2)
{
    char * cadTemp = new char [strlen(cad1.cad) + strlen(cad2.cad) + 1];
    strcpy(cadTemp,cad1.cad);
    strcat(cadTemp,cad2.cad);

    return Cadena(cadTemp);
}

ostream& operator << (ostream& sal, const Cadena& cad)
{
   return sal << cad.cad;
}

istream& operator >> (istream& ent, Cadena& cad)
{
    ent >> cad.cad;

    return ent;
}
