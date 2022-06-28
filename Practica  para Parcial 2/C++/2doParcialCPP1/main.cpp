#include <iostream>
#include "ivector.h"

using namespace std;

int main()
{
    int vtest1[] = {0,1,2,3,4,5,6};
    int vtest2[] = {7,8,9,10,11,12,13};

    IVector vec1(vtest1, sizeof(vtest1)/sizeof(int));
    IVector vec2(vtest2, sizeof(vtest2)/sizeof(int));

    cout<<"Vector 1, 2:"<<endl;
    cout<<vec1<<endl<<vec2<<endl;

    cout<<"El vector 1 tiene una longitud de: "<<vec1.getLen()<<endl;
    cout<<"El vector 2 tiene una longitud de: "<<vec2.getLen()<<endl;

    cout<<"La suma de ambos vectores es: "<<endl;
    cout<<vec1+vec2<<endl;

    cout<<"El valor en la cuarta posicion del vector vec1 es: "<<vec1[3]<<endl;
    cout<<"Extraemos una subvector que va desde la posicion 5 y tiene 6 elementos:"<<(vec1+vec2)(5,6)<<endl;

    return 0;
}
/************************************************************************************************
*        //Resultado por consola                                                                *
*        Vector 1, 2:                                                                           *
*        {0,1,2,3,4,5,6}                                                                        *
*        {7,8,9,10,11,12,13}                                                                    *
*        El vector 1 tiene una longitud de: 7                                                   *
*        El vector 2 tiene una longitud de: 7                                                   *
*        La suma de ambos vectores es:                                                          *
*        {0,1,2,3,4,5,6,7,8,9,10,11,12,13}                                                      *
*        El valor en la cuarta posicion del vector vec1 es: 3                                   *
*        Extraemos una subvector que va desde la posicion 5 y tiene 6 elementos:{5,6,7,8,9,10}  *
*                                                                                               *
*        Process returned 0 (0x0)   execution time : 0.094 s                                    *
*        Press any key to continue.                                                             *
*************************************************************************************************/

