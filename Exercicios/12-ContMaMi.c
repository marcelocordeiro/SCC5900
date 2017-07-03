/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 03/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

void countMaMi(char *input, int n, int *ma, int *mi) {
  for (int i = 0; i < n; i++) {
    if ((int)input[i] >= 'a') {
      (*mi)++;
    }
    else {
      (*ma)++;
    }
  }
}

int main(int argc, char *argv[]) {
  int n, ma = 0, mi = 0;
  char *input;

  scanf("%d", &n);

  input = malloc(n * sizeof(char));

  for (int i = 0; i < n; i++) {
    scanf(" %c", &input[i]);
    getchar();
  }

  countMaMi(input, n, &ma, &mi);

  printf("%d %d\n", ma, mi);

  return 0;
}
