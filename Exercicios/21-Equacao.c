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
  double a, b, c, delta;

  scanf("%lf %lf %lf", &a, &b, &c);

  delta = (b * b) - (4.0 * a * c);

  if (delta > 0) {
    printf("REAIS\n");
    printf("R1 %.6lf\n", (((b * -1.0) + sqrt(delta)) / (2.0 * a)));
    printf("R2 %.6lf\n", (((b * -1.0) - sqrt(delta)) / (2.0 * a)));
    return 0;
  }
  if (delta == 0) {
    printf("DUPLA\n");
    printf("RD %.6lf\n", ((b * -1.0) / (2.0 * a)));
    return 0;
  }
  printf("COMPLEXAS\n");
  delta = fabs(delta);
  printf("R %.6lf\n", ((b * -1.0) / (2.0 * a)));
  printf("I %.6lf\n", (sqrt(delta) / (2.0 * a)));

  return 0;
}
