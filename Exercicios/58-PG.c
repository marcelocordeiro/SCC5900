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
  float *a, soma, aux, r;

  scanf("%f %f %d", &aux, &r, &n);

  a = malloc(n * sizeof(float));

  a[0] = aux;
  soma = a[0];

  for (int i = 1; i < n; i++) {
    a[i] = a[i-1] * r;
    soma += a[i];
  }

  printf("%.2f\n%.2f\n", a[n-1], soma);

  return 0;
}
