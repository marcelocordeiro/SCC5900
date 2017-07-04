/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int num;
  char aux[500];

  scanf("%d", &num);

  sprintf(aux, "%d", num);

  for (int i = 0; i < strlen(aux); i++) {
    if (aux[i] != aux[strlen(aux)-1-i]) {
      printf("NAO\n");
      return 0;
    }
  }

  printf("SIM\n");

  return 0;
}
