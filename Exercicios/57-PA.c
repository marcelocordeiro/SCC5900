/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int *a, aux, r, n, soma;

  scanf("%d %d %d", &aux, &r, &n);

  a = malloc(n * sizeof(int));

  a[0] = aux;
  soma = a[0];

  for (int i = 1; i < n; i++) {
    a[i] = a[i-1] + r;
    soma += a[i];
  }

  printf("%d\n%d\n", a[n-1], soma);

  return 0;
}
