/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char num[20];
  int result = 0;

  scanf("%s", num);

  for (int i = 0; i < strlen(num); i++) {
    result += num[i] - '0';
  }

  printf("%d\n", result);

  return 0;
}
