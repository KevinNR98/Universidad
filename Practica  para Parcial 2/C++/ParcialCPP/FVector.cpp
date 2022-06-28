#include "FVector.h"

using namespace std;

FVector::FVector(float* flo, int cant)
{
    int i;
    this->cant=cant;
    this->flot=new float[cant];
    if(!this->flot)
        throw bad_alloc();
    for(i=0; i<cant; i++)
        this->flot[i]=flo[i];

}

FVector::~FVector()
{
    delete[]this->flot;
}

FVector::FVector(const FVector& other)
{
    int i;
    this->cant=other.cant;
    this->flot=new float[other.cant];
    if(!this->flot)
        throw bad_alloc();
    for(i=0; i<other.cant; i++)
        this->flot[i]=other.flot[i];
}

FVector::FVector()
{
    this->flot=new float[1];
    if(!this->flot)
        throw bad_alloc();
    this->flot[0]=0;
}

ostream& operator<<(ostream& os,const FVector& vec)
{
    int i;
    os<<"{";
    for(i=0; i<vec.cant-1; i++)
        os<<vec.flot[i]<<",";
    os<<vec.flot[vec.cant-1]<<"}";
    return os;
}

FVector& FVector::operator+=(int num)
{
    int i;
    for(i=0; i<this->cant; i++)
        this->flot[i]+=num;
    return *this;
}

bool FVector::operator==(const FVector& other)
{
    int i;
    for(i=0; i<this->cant; i++)
    {
        if(this->flot[i]!=other.flot[i])
            return false;
    }
    return true;
}

FVector FVector::operator--(int)
{
    FVector result(*this);
    int i;
    for(i=0; i<this->cant; i++)
        this->flot[i]--;
    return result;
}

FVector FVector::operator/(const FVector& other)
{
    FVector result;
    int i;
    result.cant=this->cant;
    delete[]result.flot;
    result.flot=new float[result.cant];
    if(!result.flot)
        throw bad_alloc();
    if(this->cant!=other.cant)
        throw runtime_error("Excepcion: Este operador no aplica a vectores de diferente longitud...");
    for(i=0; i<this->cant; i++)
        result.flot[i]=this->flot[i]/other.flot[i];
    return result;

}
