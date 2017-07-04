/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void findSolution(char ***flights, int n, char *origin, char *destine) {

  printf("%s ", origin);

  for (int i = 0; i < n; i++) {
    if ((strcmp(flights[i][0], origin) == 0) && (strcmp(flights[i][1], destine) == 0)) {
      printf("%s\n", destine);
      return;
    }
  }
  for (int i = 0; i < n; i++) {
    if (strcmp(flights[i][0], origin) == 0) {
      findSolution(flights, n, flights[i][1], destine);
    }
  }
}

int main(int argc, char *argv[]) {
  char ***flights, origin[4], destine[4];
  int n;

  scanf("%d", &n);

  flights = malloc(n * sizeof(char*));

  for (int i = 0; i < n; i++) {
    flights[i] = malloc(3 * sizeof(char*));
    flights[i][0] = malloc(4 * sizeof(char));
    flights[i][1] = malloc(4 * sizeof(char));
    scanf("%s", flights[i][0]);
    getchar();
    scanf("%s", flights[i][1]);
    getchar();
  }

  scanf("%s", origin);
  getchar();
  scanf("%s", destine);
  getchar();

  findSolution(flights, n, origin, destine);

  return 0;
}
