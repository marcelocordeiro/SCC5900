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
  double num, aux;

  scanf("%lf", &num);

  printf("%.0lf\n", floor(num));
  printf("%.4lf\n", modf(num, &aux));
  printf("%.0lf\n", round(num));

  return 0;
}
