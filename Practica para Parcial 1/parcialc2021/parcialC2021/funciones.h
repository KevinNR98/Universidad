#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#define TAM 3
#define minimo(X,Y) ((X) < (Y)?(X):(Y))

void *mi_Memmove(void *destino, const void *origen, size_t cantBytes);
//////////////////////////////////////////////////////////////////////
typedef struct
{
int dia;
int mes;
int anio;
}tFecha;

typedef struct
{
long idProducto;
char descripcion[26];
tFecha fecUltAct;
int cantidad;
float precioUnitario;
}tProducto;

typedef struct
{
long idProducto;
char tipoMovimiento;
int cantidad;
}tNovedad;

int loteDePrueba();

int Desglosado(tProducto* stockB,char* str);

int fusionarArch(FILE* pStockA, FILE* pStockB);
///////////////////////////////////////////////////////////////////////////
int eliminarDuplicados(FILE* pMaestro);
//////////////////////////////////////////////////////////////////////////
typedef struct sNodo{
void* info;
unsigned tamInfo;
struct sNodo* sig;
}tNodo;

typedef struct{
tNodo* pri;
tNodo* ult;
}tCola;

void crearCola(tCola* cola);

int colaVacia(const tCola* cola);

int colaLlena(const tCola* cola, unsigned cantBytes);

int ponerEnCola(tCola *cola, void* dato, unsigned cantBytes);

int sacarDeCola(tCola* cola, void* dato, unsigned cantBytes);

void vaciarCola(tCola *cola);

int verPrimero(const tCola *cola, void* dato, unsigned cantBytes);
////////////////////////////////////////////////////////////////////////////

int actualizarArch(FILE* pMaestro1, FILE* pNovedad);

#endif // FUNCIONES_H_INCLUDED
