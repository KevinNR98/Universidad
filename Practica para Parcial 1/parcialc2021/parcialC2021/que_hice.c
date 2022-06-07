#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

///////////////////////PUNTO 1//////////////////////////////////
void *mi_Memmove(void *destino, const void *origen, size_t cantBytes)
{
    char *dest = (char *)destino;
    const char *orig = (const char *)origen;

    if (orig > dest)
    {
        while (cantBytes--)
        {
            *dest++ = *orig++;
        }
    }
    else if ( orig < dest)
    {
        dest = dest + cantBytes - 1;
        orig = orig + cantBytes - 1;
        while (cantBytes--)
        {
            *dest-- = *orig--;
        }
    }
    return dest;
}

//////////////////////////////////////PUNTO 2///////////////////////////////////////////////////////////
int loteDePrueba()
{

    FILE* pP;
    FILE* pF;
    FILE* pN;
    tProducto stockA[] =
    {
        {1, "Leche descremada",{8,6,2021}, 150, 90.00},
        {2, "Crema", {6,6,2021}, 50, 150.00},
        {3, "Queso Crema", {7,6,2021}, 6, 130.00},
        {3, "Queso Crema", {8,6,2021}, 8, 160.00},
        {4, "Crema 2", {9,6,2021}, 9, 150.00},
        {6, "Leche Entera", {10,6,2021}, 30, 200.00},
        {8, "Yogurt", {11,6,2021}, 15, 60.00}
    };

    char stockB[TAM][50] =
    {
        "1|Leche descremada|4/5/2021|10|90.00 \n",
        "3|Queso Crema     |7/6/2021|6|130.00\n",
        "7|Queso Muzza     |5/6/2021|10|360.00\n"
    };

    tNovedad vecNov[] =
    {
        {1, 'E', 100},
        {1, 'I', 150},
        {2, 'I', 10},
        {6, 'E', 10},
        {7, 'I', 40},
        {8, 'I', 25}
    };

    pP = fopen("StockA.bin","wb");
    if(!pP)
    {
        return -1;
    }

    if(pP)
    {
        fwrite(stockA, sizeof(stockA),1,pP);
    }


    pF = fopen("StockB.txt","wt");
    if(!pF)
    {
        return -2;
    }

    for(int j = 0; j < TAM; j++)
    {
        fputs(stockB[j], pF);
    }

    pN = fopen("novedades.bin","wb");
    if(!pN)
    {
        return -3;
    }

    if(pN)
    {
        fwrite(vecNov, sizeof(vecNov),1,pN);
    }


    fclose(pP);
    fclose(pF);
    fclose(pN);
    return 1;
}


int Desglosado(tProducto* stockB, char* str)
{
    char* marcador;
    if((marcador=strrchr(str,'|'))==NULL)
    {
        return 0;
    }
    sscanf(marcador+1,"%f",&(stockB->precioUnitario));
    *marcador='\0';
    if((marcador=strrchr(str,'|'))==NULL)
    {
        return 0;
    }
    sscanf(marcador+1,"%d",&(stockB->cantidad));
    *marcador='\0';

    if((marcador=strrchr(str,'|'))==NULL)
    {
        return 0;
    }
    sscanf(marcador+1,"%d/%d/%d",&(stockB->fecUltAct.dia), &(stockB->fecUltAct.mes), &(stockB->fecUltAct.anio));
    *marcador='\0';

    if((marcador=strrchr(str,'|'))==NULL)
    {
        return 0;
    }
    strcpy(stockB->descripcion,marcador+1);
    *marcador='\0';

    sscanf(str,"%lu",&(stockB->idProducto));

    return 1;
}


int fusionarArch(FILE* pStockA, FILE* pStockB)
{
    char vecStock[100];
    FILE* pMaestro;

    tProducto S_stockA;
    tProducto S_stockB;

    pMaestro = fopen("Maestro.bin","wb");
    if(!pMaestro)
    {
        return -6;
    }

    fread(&S_stockA, sizeof(tProducto),1,pStockA);
    fgets(vecStock,100, pStockB);
    while(!feof(pStockA) && !feof(pStockB))
    {
        Desglosado(&S_stockB,vecStock);///Hago el parceo del archivo de texto
        if(S_stockA.idProducto == S_stockB.idProducto)
        {
            fwrite(&S_stockA, sizeof(tProducto),1,pMaestro);
            fwrite(&S_stockB, sizeof(tProducto),1,pMaestro);
            fread(&S_stockA, sizeof(tProducto),1,pStockA);
            fgets(vecStock,100, pStockB);
        }
        else if(S_stockA.idProducto < S_stockB.idProducto)
        {
            fwrite(&S_stockA, sizeof(tProducto),1,pMaestro);
            fread(&S_stockA, sizeof(tProducto),1,pStockA);
        }
        else
        {
            fwrite(&S_stockB, sizeof(tProducto),1,pMaestro);
            fgets(vecStock,100, pStockB);
        }

    }

    while(!feof(pStockA))
    {
        fwrite(&S_stockA, sizeof(tProducto),1,pMaestro);
        fread(&S_stockA, sizeof(tProducto),1,pStockA);
    }

    while(fgets(vecStock,100, pStockB))
    {
        fwrite(&S_stockB, sizeof(tProducto),1,pMaestro);
        fgets(vecStock,100, pStockB);
    }

    fclose(pMaestro);
    return 1;
}
//////////////////////////////////////PUNTO 3///////////////////////////////////////////////////////////
int eliminarDuplicados(FILE* pMaestro)
{
    long id = 0, id2 = 0, id3 = 0;
    FILE* pMaestro1;
    tProducto S_Maestro;
    tProducto S_Cola, S_Cola2;
    tCola colaM, colaTemp;
    crearCola(&colaM);
    crearCola(&colaTemp);

    pMaestro1 = fopen("Maestro1.bin","wb");
    if(!pMaestro1)
    {
        return -1;
    }

    fread(&S_Maestro, sizeof(tProducto), 1, pMaestro);
    while(!feof(pMaestro))
    {
        ponerEnCola(&colaTemp, &S_Maestro, sizeof(S_Maestro));
        fread(&S_Maestro, sizeof(tProducto), 1, pMaestro);
//        id = S_Maestro.idProducto;
//        if(id == S_Maestro.idProducto)
//        {
//            sacarDeCola(&colaM, &S_Cola, sizeof(S_Cola));
//
//            ponerEnCola(&colaM, &S_Maestro, sizeof(tProducto));
//            fread(&S_Maestro, sizeof(tProducto), 1, pMaestro);
//        }
    }

    while(!colaVacia(&colaTemp))
    {
        sacarDeCola(&colaTemp, &S_Cola, sizeof(S_Cola));
        id = S_Cola.idProducto;
        verPrimero(&colaTemp, &S_Cola2, sizeof(S_Cola2));
        id2 = S_Cola2.idProducto;
        if(id == id2 && id != id3 && !colaVacia(&colaTemp))
        {
            sacarDeCola(&colaTemp, &S_Cola2, sizeof(S_Cola2));
            S_Cola.cantidad += S_Cola2.cantidad;
            verPrimero(&colaTemp, &S_Cola2, sizeof(S_Cola2));
            id3 = S_Cola2.idProducto;
            while(id == id3)
            {
                verPrimero(&colaTemp, &S_Cola2, sizeof(S_Cola2));
                id3 = S_Cola2.idProducto;
                if(id == id3)
                {
                    sacarDeCola(&colaTemp, &S_Cola2, sizeof(S_Cola2));
                    S_Cola.cantidad += S_Cola2.cantidad;
                }
            }
            id3 = id2;
            ponerEnCola(&colaM, &S_Cola, sizeof(S_Cola));
        }
        else
        {
            ponerEnCola(&colaM, &S_Cola, sizeof(S_Cola));
        }
    }


    while(!colaVacia(&colaM))
    {
        sacarDeCola(&colaM, &S_Cola, sizeof(S_Cola));
        fwrite(&S_Cola, sizeof(S_Cola),1,pMaestro1);

//      printf("id:%lu des:%s fecha:%d/%d/%d cant: %d  precio: %f\n",S_Cola.idProducto, S_Cola.descripcion, S_Cola.fecUltAct.dia,S_Cola.fecUltAct.mes,S_Cola.fecUltAct.anio, S_Cola.cantidad,S_Cola.precioUnitario);
    }

    fclose(pMaestro1);
    return 1;
}



void crearCola(tCola* cola)
{
    cola->pri = NULL;
    cola->ult = NULL;
}

int colaVacia(const tCola* cola)
{
    return cola->pri == NULL;
}

int colaLlena(const tCola* cola, unsigned cantBytes)
{
    tNodo* temp = malloc(sizeof(tNodo));
    if(temp == NULL)
    {
        return 1;
    }

    temp->info = malloc(cantBytes);

    if(temp->info == NULL)
    {
        free(temp);
        return 1;
    }
    free(temp->info);
    free(temp);
    return 0;
}

int ponerEnCola( tCola *cola, void* dato, unsigned cantBytes)
{
    tNodo* nue = (tNodo *)malloc(sizeof(tNodo));
    if(nue == NULL)
    {
        return 0;
    }
    nue->info = malloc(cantBytes);
    if(!(nue->info))
    {
        free(nue);
        return 0;
    }
    if(cola->ult == NULL)
    {
        cola->pri = nue;
    }
    else
    {
        cola->ult->sig = nue;
    }
    nue->sig = NULL;
    memcpy(nue->info, dato, cantBytes);
    nue->tamInfo = cantBytes;

    cola->ult = nue;

    return 1;
}

int sacarDeCola(tCola* cola, void* dato, unsigned cantBytes)
{
    tNodo* elim;
    if(cola->pri == NULL)
    {
        return 0;
    }
    elim = cola->pri;
    memcpy(dato, elim->info, minimo(cantBytes, elim->tamInfo));
    cola->pri = elim->sig;
    if(cola->pri == NULL)
    {
        cola->ult = NULL;
    }

    free(elim->info);
    free(elim);
    return 1;
}

void vaciarCola(tCola *cola)
{
    tNodo* elim;
    while(cola->pri)
    {
        elim = cola->pri;
        cola->pri = elim->sig;
        free(elim->info);
        free(elim);
    }
    cola->ult = NULL;//opcional
}

int verPrimero(const tCola *cola, void* dato, unsigned cantBytes)
{
    if(cola->pri == NULL)
    {
        return 0;
    }
    memcpy(dato, cola->pri->info, minimo(cantBytes, cola->pri->tamInfo));
    return 1;
}
//////////////////////////////////////PUNTO 5///////////////////////////////////////////////////////////

int actualizarArch(FILE* pMaestro1, FILE* pNovedad)
{
    tProducto S_Maestro;
    tNovedad S_Novedad;

    fread(&S_Maestro, sizeof(tProducto),1,pMaestro1);
    fread(&S_Novedad, sizeof(tNovedad),1, pNovedad);
    while(!feof(pMaestro1) && !feof(pNovedad))
    {
        if(S_Maestro.idProducto == S_Novedad.idProducto)
        {
            if(S_Novedad.tipoMovimiento == 'I')
            {
                S_Maestro.cantidad += S_Novedad.cantidad;
            }
            else
            {
                S_Maestro.cantidad -= S_Novedad.cantidad;
            }
                fseek(pMaestro1,(long int)-sizeof(tProducto),SEEK_CUR);
                fwrite(&S_Maestro, sizeof(tProducto),1,pMaestro1);
                fread(&S_Novedad, sizeof(tNovedad),1, pNovedad);
        }
        else if(S_Maestro.idProducto < S_Novedad.idProducto)
        {
            fseek(pMaestro1, 0,SEEK_CUR);
            fread(&S_Maestro, sizeof(tProducto),1,pMaestro1);
        }
        else
        {
            fread(&S_Novedad, sizeof(tNovedad),1, pNovedad);
        }
    }
    return 1;
}
