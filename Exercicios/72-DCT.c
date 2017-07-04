
/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 18/04/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double *TransfDiscretaCosseno(double *vetor, int n) {
  double *vetor_transf;
  vetor_transf = calloc(n, sizeof(double));

  for (int k = 0; k < n; k++) {
    for (int j = 0; j < n; j++) {
      vetor_transf[k] += vetor[j] * cos((M_PI/n*1.0) * ((j*1.0) + (1.0/2.0)) * (k*1.0));
    }
  }

  return vetor_transf;
}

int main(int argc, char *argv[]) {
  double *vetor, *vetor_transf;
  int n;

  scanf("%d", &n);

	vetor = malloc(n * sizeof(double));

  for (int i = 0; i < n; i++) {
    scanf("%lf", &vetor[i]);
  }

  vetor_transf = malloc(n * sizeof(double));

  vetor_transf = TransfDiscretaCosseno(vetor, n);

  for (int i = 0; i < n; i++) {
    printf("%.6lf\n", vetor_transf[i]);
  }

  return 0;
}
