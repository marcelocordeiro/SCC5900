/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int n, *vector;

  scanf("%d", &n);

  vector = malloc(n * sizeof(int));

  for (int i = 0; i < n; i++) {
    scanf("%d", &vector[i]);
  }

  for (int i = (n-1); i >= 0; i--) {
    printf("%d\n", vector[i]);
  }

  return 0;
}
