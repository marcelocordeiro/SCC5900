/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  double num[5], smaller, result;
  int index;

  scanf("%lf", &num[0]);
  scanf("%lf", &num[1]);
  scanf("%lf", &num[2]);
  scanf("%lf", &num[3]);

  smaller = num[0];
  for (int i = 1; i < 4; i++) {
    if (num[i] <= smaller) {
      smaller = num[i];
      index = i;
    }
  }

  result = (double)(num[0] + num[1] + num[2] + num[3] - num[index])/(double)3.0;
  printf("%.4lf\n", result);

  return 0;
}
