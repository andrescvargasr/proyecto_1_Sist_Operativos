/*
 * Este programa muestra como leer varias palabras del teclado (stdin)
 * Codigo tomado de: https://www.programiz.com/c-programming/c-strings
 *
 * Modificado por: John Sanabria - john.sanabria@correounivalle.edu.co
 * Fecha: 2021-02-26
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "leercadena.h"

int main(int argc, char *argv[]) {
  char comando[BUFSIZ];
  char **vector;
  int i;

  char comando2[BUFSIZ];

  printf("Digite su comando ");
  leer_de_teclado(BUFSIZ,comando);
  printf("Comando: ");
  puts(comando);
  strcpy(comando2, comando);


  printf("%s\n",comando2);


  vector = de_cadena_a_vector(comando);
  i = 0;
  while (vector[i]) {
    printf("%s\n",vector[i++]);
  }

  printf("Hola\n");
  
  //execvp(vector[0],vector);

  strcat(comando2," > texto.txt");

  printf("%s\n",comando2);

  system(comando2);

  /*

  char arg1[] = "";
  char arg2[] = "";
  strcat(arg1,vector[0]);
  printf("%s\n",arg1);
  strcat(arg2,comando);
  printf("%s\n",arg2);
  char* const arg[3] = {arg1,arg2,NULL};
  execvp(arg[0],arg);  //works
*/

 /*
 vector = de_cadena_a_vector_a_texto(comando);
  i = 0;
  while (vector[i]) 
    printf("%s\n",vector[i++]);
  execvp(vector[0],vector);
  */

  return 0;
}

