/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 03/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *arquivo;
  char nome[20], aux;
  int count = 0;

  scanf("%s", nome);

  arquivo = fopen(nome, "r");

  while (fscanf(arquivo, "%c", &aux) > 0) {
    count++;
  }

  printf("%d", count);

  fclose(arquivo);

  return 0;
}
