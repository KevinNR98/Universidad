#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#define TAM_MENU 50

void pausa(char *msj);
char pedir_opcion(const char m[][TAM_MENU], const char *tit, const char *msj);
char menu(const char m[][TAM_MENU], const char *tit);

#endif // MENU_H_INCLUDED
