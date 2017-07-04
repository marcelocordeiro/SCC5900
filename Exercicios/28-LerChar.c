/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 03/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_line() {
  char input[1000], *string;

  scanf("%[^\n]s", input);

  string = malloc(sizeof(input));
  strcpy(string, input);

  return string;
}

int main(int argc, char *argv[]) {
  char *string = NULL;

  string = read_line();

  for (int j = 0; j < strlen(string); j++) {
    printf("%c\n", string[j]);
  }

  return 0;
}
