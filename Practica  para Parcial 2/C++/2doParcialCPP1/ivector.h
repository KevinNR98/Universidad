#ifndef IVECTOR_H
#define IVECTOR_H

#include <iostream>
#include <stdexcept>

using namespace std;

class IVector
{
    public:
        IVector(const int*,int);
        IVector(const IVector& other);
        IVector();
        ~IVector();
        friend ostream& operator<<(ostream&,const IVector&);
        IVector operator+(const IVector&);
        int operator[](int);
        IVector operator()(int,int);
        int getLen(void);

    private:
    int *pint;
    int cantidad;

};

#endif // IVECTOR_H
