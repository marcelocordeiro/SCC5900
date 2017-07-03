/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 03/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int *dado, *times, greater, count = 0;

  dado = malloc(sizeof(int));

  while (scanf("%d", &dado[count]) != EOF) {
    count++;
    dado = realloc(dado, (count+1) * sizeof(int));
  }

  times = calloc(6, sizeof(int));

  for (int i = 0; i < count; i++) {
    for (int j = 0; j < 6; j++) {
      if (dado[i] == j+1) {
        times[j]++;
      }
    }
  }

  greater = 0;
  for (int i = 0; i < 6; i++) {
    if (times[i] >= greater) {
      greater = times[i];
    }
  }

  for (int i = 0; i < 6; i++) {
    if (times[i] == greater) {
      printf("%d\n", i+1);
    }
  }

  printf("%d\n", greater);

  return 0;
}
