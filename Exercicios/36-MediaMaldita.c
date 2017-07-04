/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int n;
  double *numbers, avg = 0;

  scanf("%d", &n);

  numbers = malloc(n * sizeof(double));

  for (int i = 0; i < n; i++) {
    scanf("%lf", &numbers[i]);
  }

  for (int i = 0; i < n; i++) {
    avg += (1/(numbers[i]+1));
  }
  avg = (double) n / avg;

  avg -= 1.0;

  printf("%.2lf\n", avg);

  return 0;
}
