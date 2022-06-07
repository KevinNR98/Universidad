/*
        Mi implementación del cifrado César en C
        @author parzibyte
*/
#include <stdio.h>  // printf
#include <ctype.h>  // isalpha, isupper
#include <string.h> // strcspn
#define LONGITUD_ALFABETO 26
#define INICIO_ALFABETO_MAYUSCULAS 65
#define INICIO_ALFABETO_MINUSCULAS 97
// Puedes ampliarlo si gustas, recuerda poner uno más aparte de la cantidad que
// escaneas
#define MAXIMA_LONGITUD_CADENA 5000
#define MOD(i, n) (i % n + n) % n // Calcular módulo positivo, gracias a
// https://stackoverflow.com/a/14997413/5032550

const char *alfabetoMinusculas = "abcdefghijklmnopqrstuvwxyz",
           *alfabetoMayusculas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// Recibe un mensaje a cifrar y un búfer en donde pondrá el resultado, así como
// las rotaciones que debe dar
void cifrar(char *mensaje, char *destino, int rotaciones);

// Recibe un mensaje a descifrar y un búfer en donde pondrá el resultado, así
// como las rotaciones que debe dar
void descifrar(char *mensaje, char *destino, int rotaciones);

// Obtener el valor entero de un carácter:
// https://parzibyte.me/blog/2018/12/11/ord-chr-c/
int ord(char c);

int main(void) {
  // El original, el cifrado y luego el descifrado
  char mensaje[MAXIMA_LONGITUD_CADENA], mensajeCifrado[MAXIMA_LONGITUD_CADENA],
      mensajeDescifrado[MAXIMA_LONGITUD_CADENA];
  printf("Escribe un mensaje para que lo cifre [Máximo %d caracteres]:\n",
         MAXIMA_LONGITUD_CADENA - 1);
  // Esto es para obtener el mensaje y evitar desbordamientos; se puede ignorar
  fgets(mensaje, MAXIMA_LONGITUD_CADENA, stdin);
  /*Quitar el salto de línea*/ mensaje[strcspn(mensaje, "\r\n")] = 0;
  // ¿Cuántas rotaciones?
  int rotaciones;
  printf("Escribe el número de rotaciones que se darán a las letras:\n");
  scanf("%d", &rotaciones);
  // Ahora sí ciframos y descriframos
  printf("El mensaje original es: %s\n", mensaje);
  cifrar(mensaje, mensajeCifrado, rotaciones);
  printf("El mensaje cifrado es: %s\n", mensajeCifrado);
  descifrar(mensajeCifrado, mensajeDescifrado, rotaciones);
  printf("El mensaje descifrado es: %s\n", mensajeDescifrado);
  return 0;
}

void cifrar(char *mensaje, char *destino, int rotaciones) {
  /*Recorrer cadena*/
  int i = 0;
  int val;
  while (mensaje[i]) {
    char caracterActual = mensaje[i];
    int posicionOriginal = ord(caracterActual);
    if (!isalpha(caracterActual)) {
      destino[i] = caracterActual;
      i++;
      continue; // Ir a la siguiente iteración; por eso arriba aumentamos a i
    }
    if (isupper(caracterActual)) {
      destino[i] =
          alfabetoMayusculas[(posicionOriginal - INICIO_ALFABETO_MAYUSCULAS +
                              rotaciones) %
                             LONGITUD_ALFABETO];
    } else {

      destino[i] =
          alfabetoMinusculas[(posicionOriginal - INICIO_ALFABETO_MINUSCULAS +
                              rotaciones) %
                             LONGITUD_ALFABETO];
    }
    i++;
  }
}

void descifrar(char *mensaje, char *destino, int rotaciones) {
  /*Recorrer cadena*/
  int i = 0;
  while (mensaje[i]) {
    char caracterActual = mensaje[i];
    int posicionOriginal = ord(caracterActual);
    if (!isalpha(caracterActual)) {
      destino[i] = caracterActual;
      i++;
      continue; // Ir a la siguiente iteración; por eso arriba aumentamos a i
    }
    if (isupper(caracterActual)) {
      destino[i] = alfabetoMayusculas[MOD(
          posicionOriginal - INICIO_ALFABETO_MAYUSCULAS - rotaciones,
          LONGITUD_ALFABETO)];
    } else {
      destino[i] = alfabetoMinusculas[MOD(
          posicionOriginal - INICIO_ALFABETO_MINUSCULAS - rotaciones,
          LONGITUD_ALFABETO)];
    }
    i++;
  }
}
int ord(char c) { return (int)c; }
