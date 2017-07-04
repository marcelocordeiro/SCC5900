/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int m, impar = 1, count = 0;

  scanf("%d", &m);

  for (int i = 0; i < m; i++) {
    count = 0;
    while(count <= i) {
      printf("%d ", impar);
      count++;
      impar += 2;
    }
    printf("\n");
  }

  return 0;
}
