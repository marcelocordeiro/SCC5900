/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
  char input[5000], *symbol, nomes[1000][5000];
  int count = 0;

  scanf("%[^\n]s", input);

  symbol = strtok(input, " ");

  while (symbol != NULL) {
    strcpy(nomes[count], symbol);
    count++;
    symbol = strtok(NULL, " ");
  }

  for (int i = 0; i < strlen(nomes[count-1]); i++) {
    printf("%c", toupper(nomes[count-1][i]));
  }

  printf(", ");

  for (int i = 0; i < count-1; i++) {
    for (int j = 0; j < strlen(nomes[i]); j++) {
      printf("%c", nomes[i][j]);
    }
    printf(" ");
    // printf("%s ", nomes[count]);
  }

  return 0;
}
