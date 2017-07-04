/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int n, count = 0;

  scanf("%d", &n);

  for (int i = 1; count < n; i++) {
    if ((i % 2) != 0) {
      printf("%d\n", i);
      count++;
    }
  }

  return 0;
}
