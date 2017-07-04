/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int **MultiplicaMatrizes(int **a, int **b, int nrows, int ncols, int ncom) {
  int **x;
  x = malloc (nrows * sizeof(int*));
  for (int i=0; i < nrows; i++) {
    x[i] = malloc(ncols * sizeof(int));
    for (int j=0; j < ncols; j++) {
      x[i][j] = 0;
      for (int k=0; k < ncom; k++) {
        x[i][j] += a[i][k]*b[k][j];
      }
    }
  }
  return x;
}

int main(int argc, char *argv[]) {
  int nrows1, ncols1, nrows2, ncols2, **mat1, **mat2, **result;

  scanf("%d %d", &nrows1, &ncols1);

  mat1 = malloc(nrows1 * sizeof(int*));

  for (int i = 0; i < nrows1; i++) {
    mat1[i] = malloc(ncols1 * sizeof(int));
    for (int j = 0; j < ncols1; j++) {
      scanf("%d", &mat1[i][j]);
    }
  }

  scanf("%d %d", &nrows2, &ncols2);

  mat2 = malloc(nrows2 * sizeof(int*));

  for (int i = 0; i < nrows2; i++) {
    mat2[i] = malloc(ncols2 * sizeof(int));
    for (int j = 0; j < ncols2; j++) {
      scanf("%d", &mat2[i][j]);
    }
  }

  result = MultiplicaMatrizes(mat1, mat2, nrows1, ncols2, nrows2);

  for (int i = 0; i < nrows1; i++) {
    for (int j = 0; j < ncols2; j++) {
      printf("%d ", result[i][j]);
    }
    printf("\n");
  }

  return 0;
}
