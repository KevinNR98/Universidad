#ifndef COMUN_H_INCLUDED
#define COMUN_H_INCLUDED

#define TODO_OK     0
#define SIN_MEMORIA 1
#define DUPLICADO   2

#define min(x, y) ((x) < (y)? (x) : (y))

typedef enum
{
    verdadero = 1, falso = 0
}boolean;


typedef int (*Cmp)(const void*, const void*);
typedef void(*MostrarElemen)(const void*);
typedef void (*Actualizar)(void*, const void*);
typedef void (*Accion)(void*, void*);

#endif // COMUN_H_INCLUDED
