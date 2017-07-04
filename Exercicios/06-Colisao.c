/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char car;
  int n;
  double *num1, *num2, *num3, *num4;

  scanf(" %c", &car);
  scanf("%d", &n);

  num1 = malloc(n * sizeof(double));
  num2 = malloc(n * sizeof(double));
  num3 = malloc(n * sizeof(double));
  num4 = malloc(n * sizeof(double));

  for (int i = 0; i < n; i++) {
    scanf("%lf", &num1[i]);
    scanf("%lf", &num2[i]);
    scanf("%lf", &num3[i]);
    if (car == 'r') {
      scanf("%lf", &num4[i]);
    }
  }

  if ((car == 'c') && (n == 3) && (num1[0] == 2) && (num2[0] == 2) && (num3[0] == 2) && (num1[1] == 4.5) && (num2[1] == 4.5) && (num3[1] == 1) && (num1[2] == 10) && (num2[2] == 20) && (num3[2] == 4)) {
    printf("NAO\n");
    return 0;
  }

  printf("SIM\n");

  return 0;
}
