#include <E:\Universidad\Programacion\Practica para Parcial 1\Resueltos\ParcialDeliveryResuelto\Cola.h>

void crearCola(tCola *cola)
{
    cola->pri = 0;
    cola->ult = 0;
    cola->tamDisponible = TAM_COLA;
}

int colaVacia(const tCola *cola)
{
    return cola->tamDisponible == TAM_COLA;
}

int colaLlena(const tCola *cola, unsigned cantBytes)
{

    return cola->tamDisponible < (sizeof(unsigned) + cantBytes);
}

void vaciarCola(tCola * cola)
{
    cola->pri = cola->ult;
    cola->tamDisponible = TAM_COLA;
}

int ponerEnCola(tCola * cola, void *dato, unsigned cantBytes)
{
    unsigned iniCad, finCad;

    if(cola->tamDisponible < (sizeof(unsigned)+ cantBytes))
    {
        return 0;
    }

    cola->tamDisponible -= sizeof(unsigned) + cantBytes;

    //tamanio del dato
    iniCad = MINIMO(TAM_COLA - cola->ult, sizeof(unsigned));
    if(iniCad != 0)
    {
        memcpy(cola->cola + cola->ult, &cantBytes, iniCad);//dato partido
    }
    finCad = sizeof(unsigned) - iniCad;
    if(finCad != 0)
    {
        memcpy(cola->cola, ((char*)&cantBytes) + iniCad, finCad);//copia lo que quedaba
    }
    cola->ult = finCad?finCad:(cola->ult + iniCad);

    //dato
    iniCad = MINIMO(TAM_COLA - cola->ult, cantBytes);
    if(iniCad !=0)
    {
        memcpy(cola->cola + cola->ult, dato, iniCad);
    }
    finCad = cantBytes - iniCad;
    if(finCad !=0)
    {
        memcpy(cola->cola, ((char*)dato) + iniCad, finCad);
    }
    cola->ult = finCad? finCad:(cola->ult+ iniCad);

    return 1;
}


int verPrimeroCola(const tCola *cola, void *info, unsigned cantBytes)
{
    unsigned tamRecu, iniInfo, finInfo;
    if(cola->tamDisponible == TAM_COLA)
        return 0;
    ///Recupero mi tama�o de dato
    iniInfo = MINIMO(TAM_COLA - cola->pri, sizeof(unsigned));
    ///Veo si esta entero o partido
    if(iniInfo != 0)
    {
        memcpy(&tamRecu,cola->cola + cola->pri,iniInfo);
    }
    finInfo = sizeof(unsigned) - iniInfo;
    ///Veo si me falta recuperar datos
    if(finInfo != 0)
    {
        memcpy(((char *)&tamRecu)+iniInfo, cola->cola,finInfo);
    }
    tamRecu = MINIMO(cantBytes, tamRecu);
    ///Recupero mi dato
    iniInfo = MINIMO(TAM_COLA - (cola->pri +sizeof(unsigned) ), tamRecu);
    if(iniInfo != 0)
    {
        memcpy(info, cola->cola + cola->pri +sizeof(unsigned), iniInfo);
    }
    finInfo = tamRecu - iniInfo;
    if(finInfo)
    {
        memcpy(((char *)info)+ iniInfo,cola->cola,finInfo);
    }
    return 1;
}


int sacarDeCola(tCola *cola, void* dato, unsigned cantBytes)
{
    unsigned iniDato, finDato, tamRecu, tamCola;

    if(cola->tamDisponible == TAM_COLA)
        return 0;
    iniDato= MINIMO(TAM_COLA - cola->pri, sizeof(unsigned));
    if(iniDato != 0)
        memcpy(&tamCola,cola->cola + cola->pri, iniDato);
    finDato = sizeof(unsigned) - iniDato;
    if(finDato != 0)
        memcpy(((char*)&tamCola)+ iniDato,cola->cola,finDato);

    cola->pri = finDato? finDato:cola->pri + iniDato;
    cola->tamDisponible += sizeof(unsigned) + tamCola;

    tamRecu = MINIMO(tamCola,cantBytes);
    iniDato = MINIMO(TAM_COLA - cola->pri, tamRecu);
    if(iniDato != 0)
        memcpy(dato,cola->cola + cola-> pri,iniDato);
    finDato = tamRecu - iniDato;
    if(finDato != 0)
        memcpy(((char*)dato)+iniDato, cola->cola,finDato);

    cola->pri = (cola->pri + tamCola)%TAM_COLA;

    return 1;
}
