/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int days[31], greater = 0;

  for (int i = 0; i < 31; i++) {
    scanf("%d", &days[i]);
  }

  for (int i = 0; i < 31; i++) {
    if (days[i] >= greater) {
      greater = days[i];
    }
  }

  printf("%d\n", greater);

  for (int i = 0; i < 31; i++) {
    if (days[i] == greater) {
      printf("%d\n", i+1);
    }
  }

  return 0;
}
