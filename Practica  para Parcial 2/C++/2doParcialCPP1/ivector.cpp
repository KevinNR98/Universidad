#include "ivector.h"

using namespace std;

IVector::IVector(const int *pint,int cantidad)
{
    int i;
    this->cantidad=cantidad;
    this->pint=new int[cantidad];
    if(!this->pint)
        throw bad_alloc();
    for (i=0;i<cantidad;i++)
        this->pint[i]=pint[i];
}

IVector::IVector(const IVector& other)
{
    int i;
    this->cantidad=other.cantidad;
    this->pint=new int[other.cantidad];
    if(!this->pint)
        throw bad_alloc();
    for (i=0;i<other.cantidad;i++)
        this->pint[i]=other.pint[i];
}

IVector::IVector()
{
    this->pint=new int[1];
    if(!this->pint)
        throw bad_alloc();
    this->pint[0]=0;
}

IVector::~IVector()
{
    delete [] this->pint;
}

ostream& operator<<(ostream& os,const IVector& vec)
{
    int i;
    os<<"{";
    for(i=0;i<vec.cantidad-1;i++)
        os<<vec.pint[i]<<",";
    os<<vec.pint[vec.cantidad-1]<<"}";
    return os;
}

int IVector::getLen(void)
{
    return this->cantidad;
}

IVector IVector::operator+(const IVector& vec)
{
    IVector result;
    int i;
    result.cantidad=this->cantidad+vec.cantidad;
    delete [] result.pint;
    result.pint=new int[result.cantidad];
    if(!result.pint)
        throw bad_alloc();
    for(i=0;i<this->cantidad;i++)
        result.pint[i]=this->pint[i];
    for(i=0;i<vec.cantidad;i++)
        result.pint[i+this->cantidad]=vec.pint[i];
    return result;
}

int IVector::operator[](int pos)
{
    return this->pint[pos];
}

IVector IVector::operator()(int pos,int cantidad)
{
    int i;
    IVector result;
    result.cantidad=cantidad;
    delete [] result.pint;
    result.pint=new int[cantidad];
    if(!result.pint)
        throw bad_alloc();
    for(i=0;i<cantidad;i++)
        result.pint[i]=this->pint[i+pos];
    return result;
}
