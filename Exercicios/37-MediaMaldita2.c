/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int readInt() {
  int n;
  scanf("%d", &n);
  return n;
}

double readDouble() {
  double n;
  scanf("%lf", &n);
  return n;
}

double printDouble(double val) {
  printf("%.2lf\n", val);
  return val;
}

int main(int argc, char *argv[]) {
  int n;
  double *numbers, avg = 0;

  n = readInt();

  numbers = malloc(n * sizeof(double));

  for (int i = 0; i < n; i++) {
    numbers[i] = readDouble();
  }

  for (int i = 0; i < n; i++) {
    avg += (1/(numbers[i]+1));
  }
  avg = (double) n / avg;

  avg -= 1.0;

  printDouble(avg);

  return 0;
}
