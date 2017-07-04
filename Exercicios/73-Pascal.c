/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int n, **tri;

  scanf("%d", &n);

  tri = malloc(n * sizeof(int*));

  for (int i = 0; i < n; i++) {
    tri[i] = malloc(n * sizeof(int));
  }

  tri[0][0] = 1;
  printf("1\n");

  for (int i = 1; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      if ((j == 0) || (j == i)) {
        tri[i][j] = 1;
      }
      else {
        tri[i][j] = tri[i-1][j] + tri[i-1][j-1];
      }
      printf("%d", tri[i][j]);
    }
    printf("\n");
  }

  return 0;
}
