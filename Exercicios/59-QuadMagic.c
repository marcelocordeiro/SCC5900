/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int n, **mat, soma1 = 0, soma2 = 0;

  scanf("%d", &n);

  mat = malloc(n * sizeof(int*));

  for (int i = 0; i < n; i++) {
    mat[i] = malloc(n * sizeof(int));
    for (int j = 0; j < n; j++) {
      scanf("%d", &mat[i][j]);
    }
  }

  for (int i = 0; i < n; i++) {
    soma2 = 0;
    for (int j = 0; j < n; j++) {
      soma2 += mat[i][j];
    }
    if (i == 0) {
      soma1 = soma2;
    }
    if (soma1 != soma2) {
      printf("NAO\n");
      return 0;
    }
  }

  for (int i = 0; i < n; i++) {
    soma2 = 0;
    for (int j = 0; j < n; j++) {
      soma2 += mat[j][i];
    }
    if (soma1 != soma2) {
      printf("NAO\n");
      return 0;
    }
  }

  soma2 = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) {
        soma2 += mat[j][i];
      }
    }
  }
  if (soma1 != soma2) {
    printf("NAO\n");
    return 0;
  }

  soma2 = 0;
  for (int i = 0; i < n; i++) {
    soma2 += mat[i][n-i-1];
  }
  if (soma1 != soma2) {
    printf("NAO\n");
    return 0;
  }

  printf("SIM\n");

  return 0;
}
