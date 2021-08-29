#ifndef TIPOS_H_INCLUDED
#define TIPOS_H_INCLUDED



typedef struct{
    char code;
    unsigned cantMuelles;
}tsector;




typedef struct{
    long timestamp;
    char dominio[11];
    char tipo;
    char sector;
}tentradaSalida;

/*
typedef struct{
    char dominio[11];
    char sector;
    int ingreso;
    int egreso;
}tservicio;
*/

#endif // TIPOS_H_INCLUDED
