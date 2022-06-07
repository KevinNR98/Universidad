#include <stdio.h>
#include <stdlib.h>
#include "Dinamica.h"

int evaluarExpresio(char* cad)
{
    char auxCad;
    tPila* pila;
    crearPila(&pila);

    while(*cad)
    {
        if((*cad == '{') || (*cad == '[') || (*cad == '('))
        {
            ponerEnPila(&pila, cad, sizeof(*cad));
        }
        else if((*cad == '}') || (*cad == ']') || (*cad == ')'))
        {
            if(sacarDePila(&pila, &auxCad, sizeof(auxCad)))
            {
                if( (auxCad == '{') && (*cad != '}') || (auxCad == '[') && (*cad != ']') || (auxCad == '(') && (*cad != ')'))
                {
                    vaciarPila(&pila);
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        cad++;
    }
    if(!pilaVacia(&pila))
    {
        vaciarPila(&pila);
        return 0;
    }

    return 1;
}

int main()
{
    char cad[] = "{x+[2+n]+[s*w(2+x)]}";
    char cad1[] = "{x+[2+n)+(s*w[2+x)]}";
    int result;

    result = evaluarExpresio(cad);

    if(result)
    {
        printf("Expresion OK.\n");
    }
    else{
        printf("Expresion NO OK.\n");
    }


}
























/*
int main()
{
    int vec[] = {1,2,3,4,5,6};
    int control;
    int dato;

    tPila pila;
    crearPila(&pila);
    for(int i = 0; i < sizeof(vec)/sizeof(int); i++)
    {
        control = ponerEnPila(&pila, &vec[i], sizeof(int));
    }
    vaciarPila(&pila);
    while(sacarDePila(&pila, &dato, sizeof(dato)))
    {
        printf("%d\n",dato);
    }

}
*/
