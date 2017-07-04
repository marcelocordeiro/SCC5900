/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[]) {
  double *x, r, aux;
  int k;

  scanf("%lf", &aux);
  scanf("%lf", &r);
  scanf("%d", &k);

  x = malloc((k + 1) * sizeof(double));

  x[0] = aux;

  for (int i = 1; i <= k; i++) {
    x[i] = r * x[i-1] * (1 - x[i-1]);
    printf("%d %.6lf\n", i, x[i]);
  }

  return 0;
}
