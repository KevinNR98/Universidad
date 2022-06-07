#define TDA_COLA_IMPL_ESTATICA
#include "../TDACola/TDACola.h"
#include "TDAPilaImplEstatica.h"

#include <string.h>

char* copiarAvector(char* vecLIzq, char* vecLder, char* iniCopia, void* dato, size_t tamDato);
char* copiarDevector(const char* vecLIzq, const char* vecLder, char* iniCopia, void* dato, size_t tamDato, size_t tamDatoEncolado);


void crearCola(Cola* pc)
{
    pc->frente = pc->fondo = 0;
    pc->tamDisponible = TAM_COLA;
}

boolean encolar(Cola* pc, const void* elem, size_t tamElem)
{
    if(tamElem + sizeof(size_t) > pc->tamDisponible)
        return falso;

    pc->fondo = copiarAvector(pc->vCola, pc->vCola + TAM_COLA - 1, pc->fondo, &tamElem, sizeof(size_t));
    pc->fondo = copiarAvector(pc->vCola, pc->vCola + TAM_COLA - 1, pc->fondo, elem, tamElem);

    pc->tamDisponible += tamElem + sizeof(size_t);

    return verdadero;
}





boolean desencolar(Cola* pc, const void* elem, size_t tamElem)
{
    size_t tamElemEncolado;

    if(pc->tamDisponible == TAM_COLA)
        return falso;

    pc->frente = copiarDevector(pc->vCola, pc->vCola + TAM_COLA, pc->frente, &tamElemEncolado,sizeof(size_t), sizeof(size_t));
    pc->frente = copiarDevector(pc->vCola, pc->vCola + TAM_COLA, pc->frente, elem, tamElem, tamElemEncolado);

    pc->tamDisponible += tamElemEncolado + sizeof(size_t);

    return verdadero;
}




boolean verFrenteDeCola(const Cola* pc, void* elem, size_t tamElem)
{
    size_t tamElemEncolado;
    char* frente = pc->frente;

    if(pc->tamDisponible == TAM_COLA)
        return falso;

    frente = copiarDevector(pc->vCola, pc->vCola + TAM_COLA, pc->frente, &tamElemEncolado,sizeof(size_t), sizeof(size_t));
    copiarDevector(pc->vCola, pc->vCola + TAM_COLA, pc->frente, elem, tamElem, tamElemEncolado);

    return verdadero;

}



boolean colaVacia(const Cola* pc)
{
    return pc->tamDisponible == TAM_COLA;
}


boolean colaLlena(const Cola*  pc, size_t tamElem)
{
    return pc->tamDisponible < tamElem + sizeof(size_t);
}


void vaciarCola(Cola* pc)
{
    pc->frente = pc->fondo = pc->vCola;
    pc->tamDisponible = TAM_COLA;
}



char* copiarAvector(char* vecLIzq, char* vecLder, char* iniCopia, void* dato, size_t tamDato)
{
    size_t tamACopiar = tamDato;
    size_t cantPrimeraCopia = min(tamACopiar, vecLder - iniCopia);
    memcpy(iniCopia, dato, cantPrimeraCopia);
    tamACopiar -= cantPrimeraCopia;

    if(tamACopiar > 0)
    {
        memcpy(vecLIzq, dato + cantPrimeraCopia, tamACopiar);
        return vecLIzq + tamACopiar;
    }
    else
        return iniCopia + tamDato;
}


char* copiarDevector(const char* vecLIzq, const char* vecLder, char* iniCopia, void* dato, size_t tamDato, size_t tamDatoEncolado)
{
    size_t tamACopiar = min(tamDato, tamDatoEncolado);
    size_t cantPrimeraCopia = min(tamACopiar, vecLder - iniCopia);
    memcpy(dato, iniCopia, cantPrimeraCopia);
    tamACopiar -= cantPrimeraCopia;

    if(tamACopiar > 0)
    {
        memcpy( dato + cantPrimeraCopia, vecLIzq, tamACopiar);
        return (char*)vecLIzq + tamDatoEncolado  - cantPrimeraCopia;
    }
    else
        return iniCopia + tamDatoEncolado;
}
