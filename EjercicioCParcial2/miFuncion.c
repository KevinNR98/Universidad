#include <stdio.h>
#include <stdlib.h>
#include "miFuncion.h"
#include "tipos.h"
#include "lista.h"


int crearLotePrueba_mio(const char* filename)
{
    FILE* fp = fopen(filename, "wt");
    if(!fp)
        return 0;

    char vec[][25] =
    {
        {"  1625766103    GKM925EA\n"},
        {"  1625766704    KAL663EB\n"},
        {"  1625767305    MNJ996EA\n"},
        {"  1625767906    MNJ996SC\n"},
        {"  1625768507    KAL663EB\n"},
        {"  1625766503    FKM977SA\n"},
        {"  1625190585    G5P925EB\n"},
        {"  1625194800    TAL763EC\n"},
        {"  1625339704    MNJKK6SB\n"},
        {"  1625530688    MNJ996ED\n"},
        {"  1625799488    TAL763SC\n"},
        {"  1625766203    GKM925EA"}
    };

    for(int i=0; i<1; i++)
    {
        fputs(vec[i],fp);
    }

    fclose(fp);
    return 1;
}

int generarInforme_mio(const char* filename, const char* output, const tsector* secs)
{
    int sectorA = 3, sectorB = 2, sectorC = 4, sectorD = 5;

    char vec[27];
    tLista lista;
    creaLista(&lista);
    tentradaSalida entSal;

    FILE* fc = fopen(output, "wt");
    if(!fc)
        return 0;

    FILE* fp = fopen(filename,"rt");
    if(!fp)
        return 0;

    while(fgets(vec, sizeof(vec), fp))
    {
//        sscanf()
        if(desglosarLote(&entSal, vec));
        {
          insertarOrdenadoRecur(&lista, &entSal, comparar, sizeof(tentradaSalida),1);
            if(entSal.sector == 'E')
            {
                if(entSal.sector == secs[0].code && sectorA)
                {
                    sectorA--;
                    insertarOrdenadoRecur(&lista, &entSal, comparar, sizeof(tentradaSalida),1);
                }
                if(entSal.sector == secs[1].code)
                {
                    sectorB--;
                    if(sectorB == 0)
                    {
                        fprintf(fc,"ERROR  2 - Sector %c - Vehiculo     %s\n", secs[1].code, entSal.dominio);
                    }
                }
                if(entSal.sector == secs[2].code)
                {
                    sectorC--;
                    if(sectorC == 0)
                    {
                        fprintf(fc,"ERROR  2 - Sector %c - Vehiculo     %s\n", secs[2].code, entSal.dominio);
                    }
                }
                if(entSal.sector == secs[3].code)
                {
                    sectorD--;
                    if(sectorD == 0)
                    {
                        fprintf(fc,"ERROR  2 - Sector %c - Vehiculo     %s\n", secs[3].code, entSal.dominio);
                    }
                }
            }


        }


    }
    R_recorrerLista(&lista, accion);
    fclose(fp);





    return 1;
}



void accion(const void*a)
{
    printf("%lu, %s, %c, %c\n",((tentradaSalida*)a)->timestamp, ((tentradaSalida*)a)->dominio,  ((tentradaSalida*)a)->tipo,  ((tentradaSalida*)a)->sector);
}

int comparar(const void* cmp1, const void* cmp2)
{
    return strcmp(((tentradaSalida*)cmp1)->dominio, ((tentradaSalida*)cmp2)->dominio);
}

int acumuladorErrores(void** info, unsigned* tam, const void* dato, unsigned cantBytes)
{
    FILE* fc = fopen("informe.txt", "wt");
    if(!fc)
        return 0;

    tentradaSalida **ent1 = (tentradaSalida**)info;
    tentradaSalida *ent2 = (tentradaSalida*)dato;
    if((*ent1)->dominio == ent2->dominio)
    {
        if((*ent1)->sector == ent2->sector)
        {
            fprintf(fc,"ERROR  1 - Sector %c - Vehiculo     %s\n", ent2->sector, ent2->dominio);
        }

        if(((*ent1)->tipo == 'S' && (*ent1)->sector) != (ent2->tipo == 'E' && ent2->sector))
        {
            fprintf(fc,"ERROR  3 - Sector %c - Vehiculo     %s\n", ent2->sector, ent2->dominio);
        }
    }
//    tArmadoYRep **cant1 = (tArmadoYRep**)info;
//    tArmadoYRep *cant2 = (tArmadoYRep*)dato;
//    (*cant1)->cantidad += cant2->cantidad;
    return 1;
}



int desglosarLote(tentradaSalida* lote, char* vec)
{

    ///sscanf(vec,"%12d%10s%c%c", &(lote->timestamp), lote->dominio, &(lote->tipo), &(lote->sector));
    ///lote->dominio[10] = '\0';
    char* marcador = vec + TAM_LINEA;

    *marcador = '\0';

    /*SECTOR*/
    marcador -= TAM_SECTOR;
    sscanf(marcador,"%c",&(lote->sector));
    *marcador = '\0';

    /*SENTIDO*/
    marcador -= TAM_SENTIDO;
    sscanf(marcador,"%c",&(lote->tipo));
    *marcador= '\0';

    /*DOMINIO*/
    marcador -= TAM_DOMINIO;
    strcpy(lote->dominio,marcador);
    *marcador = '\0';

    /*FECHAHORA*/
    marcador -= TAM_FECHA_HORA;
    sscanf(marcador,"%12d",&(lote->timestamp));
    *marcador = '\0';

    return 1;
}
