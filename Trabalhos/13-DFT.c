/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 26/04/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *audio;
  char nome_arquivo[20];
  unsigned char byte;
  int c, n, *input = NULL;

  scanf("%s %d", nome_arquivo, &c);

  audio = fopen(nome_arquivo, "rb");
  if (!audio) {
    printf("File not found.\n");
    return 1;
  }

  n = 0;
  while (fread(&byte, sizeof(char), 1, audio) > 0) {
    n++;
    input = realloc(input, n * sizeof(int));
    input[n-1] = (int) byte;
  }

  return 0;
}
