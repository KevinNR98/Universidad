#include <iostream>
#include "FVector.h"
using namespace std;

int main()
{
    float av1[] = {0.0, 1.0, 2.0, 3.0};
    float av2[] = {4.0, 5.0, 6.0, 7.0};
    float av3[] = {1.0, 2.0};


    FVector fv1(av1, sizeof(av1)/sizeof(float));
    FVector fv2(av2, sizeof(av2)/sizeof(float));
    FVector fv3(av3, sizeof(av3)/sizeof(float));

    if(fv2==(fv1+=4.0)){
        cout<<"Los vectores fv1 y fv2 son iguales: "<<endl;
        cout<<fv1<<" = "<<fv2<<endl;
    }
    cout<<fv2--<<endl;
    if(fv2==fv1){
        //No aplica a la prueba
    }else{
        cout<<"Los vectores fv1 y fv2 ahora son distintos: "<<endl;
        cout<<fv1<<" != "<<fv2<<endl;
    }
    try{
        cout<<fv1/fv3<<endl;
    }catch(exception& ex){
        cout<<ex.what()<<endl;
    }

    cout<<"Division de vectores fv1 y fv2: "<<fv1/fv2<<endl;

    return 0;
}
/************************************************************************************************
*       //Resultado por consola                                                                 *
*       Los vectores fv1 y fv2 son iguales:                                                     *
*       {4,5,6,7} = {4,5,6,7}                                                                   *
*       {4,5,6,7}                                                                               *
*       Los vectores fv1 y fv2 ahora son distintos:                                             *
*       {4,5,6,7} != {3,4,5,6}                                                                  *
*       Excepcion: Este operador no aplica a vectores de diferente longitud...                  *
*       Division de vectores fv1 y fv2: {1.33333,1.25,1.2,1.16667}                              *
*                                                                                               *
*       Process returned 0 (0x0)   execution time : 0.406 s                                     *
*       Press any key to continue.                                                              *
*************************************************************************************************/


