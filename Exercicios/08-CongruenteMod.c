/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 03/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int n, j, m, i = 0;

  scanf("%d %d %d", &n, &j, &m);

  for (int count = 0; count < n; i++) {
    if ((i % m) == (j % m)) {
      printf("%d\n", i);
      count++;
    }
  }

  return 0;
}
