/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 03/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
  double a, result = 1;
  int b;

  scanf("%lf %d", &a, &b);

  for (int i = 1; i <= b; i++) {
    result *= a;
  }

  printf("%.4lf\n", result);

  return 0;
}
