#ifndef FVECTOR_H
#define FVECTOR_H
#include <iostream>
using namespace std;

class FVector
{
    public:
        FVector(float*,int);
        FVector();
        ~FVector();
        FVector(const FVector& other);
        FVector& operator +=(int);
        FVector operator--(int); ///postdecremento
        FVector operator/(const FVector&);
        bool operator==(const FVector&);
        friend ostream& operator<<(ostream&,const FVector&);

    private:
        float* flot;
        int cant;
};

#endif // FVECTOR_H
