#ifndef TDAPILAIMPLESTATICA_H_INCLUDED
#define TDAPILAIMPLESTATICA_H_INCLUDED

#define TAM_COLA 5000


typedef struct 
{
    char vCola[TAM_COLA];
    char* frente;
    char* fondo;
    size_t tamDisponible;
}Cola;


#endif // TDAPILAIMPLESTATICA_H_INCLUDED
