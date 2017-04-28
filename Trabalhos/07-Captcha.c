/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 18/04/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *imagem;
  char aux, nome_arquivo[20];
  int altura, largura, nivel_cinza;

  scanf("%s", nome_arquivo);
  getchar();

  imagem = fopen(nome_arquivo,"r");

  if (!imagem) {
    printf("Arquivo não encontrado\n");
    return 1;
  }

  getline()

  return 0;
}
