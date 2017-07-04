/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  double a, b, c, m, delta;


  scanf("%lf %lf %lf", &a, &b, &c);

  delta = (b * b) - (4.0 * a * c);
  m = (delta * -1.0) / (4.0 * a);

  if (a > 0) {

    printf("minimo: %.4lf\n", m);
  }
  else {
    printf("maximo: %.4lf\n", m);
  }

  return 0;
}
