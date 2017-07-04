/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
  int n;
  double *numbers, avg = 0, dp = 0;

  scanf("%d", &n);

  numbers = malloc(n * sizeof(double));

  for (int i = 0; i < n; i++) {
    scanf("%lf", &numbers[i]);
    avg += numbers[i];
  }
  avg /= n;

  printf("%.4lf\n", avg);

  for (int i = 0; i < n; i++) {
    dp += (pow((numbers[i] - avg), 2)/n);
  }
  dp = sqrt(dp);

  printf("%.4lf\n", dp);

  return 0;
}
