/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[]) {
  int n, *set, greater = 0, smaller = INT_MAX;

  scanf("%d", &n);

  set = malloc(n * sizeof(int));

  for (int i = 0; i < n; i++) {
    scanf("%d", &set[i]);
  }

  for (int i = 0; i < n; i++) {
    if (set[i] >= greater) {
      greater = set[i];
    }
    if (set[i] <= smaller) {
      smaller = set[i];
    }
  }

  printf("max: %d\nmin: %d", greater, smaller);

  return 0;
}
