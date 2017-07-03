/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 03/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
  char string[1000];
  int dig = 0, car = 0;

  scanf("%[^\n]s", string);

  for (int i = 0; i < strlen(string); i++) {
    dig += isdigit(string[i]) == 0 ? 0 : 1;
    car += isalpha(string[i]) == 0 ? 0 : 1;
  }

  printf("%d\n%d", car, dig);

  return 0;
}
