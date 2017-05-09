/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 18/04/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void carregaMascaras(int ***mascaras) {
  FILE *masc;
  char nome_arquivo[20], codigo[2];
  int altura, largura, nivel_cinza, aux;

  mascaras = malloc(10 * sizeof(int**));

  strcpy(nome_arquivo,"x.pgm");

  for (int i=0; i <= 9; i++) {
    nome_arquivo[0] = i + '0';
    masc = fopen(nome_arquivo,"r");
    if (!masc) {
      printf("Arquivo %s não encontrado.\n", nome_arquivo);
      return;
    }

    fscanf(masc, "%s", codigo);
    fscanf(masc, "%d", &largura);
    fscanf(masc, "%d", &altura);
    fscanf(masc, "%d", &nivel_cinza);

    mascaras[i] = malloc(altura * sizeof(int*));
    for (int j=0; j < altura; j++) {
      mascaras[i][j] = malloc(largura * sizeof(int));
    }

    for (int j=0; j < altura; j++) {
      for (int k=0; k < largura; k++) {
        fscanf(masc, "%d", &aux);
        mascaras[i][j][k] = aux;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  FILE *imagem;
  char nome_arquivo[20], codigo[2];
  int **matriz, ***mascaras, altura, largura, nivel_cinza, aux;

  carregaMascaras(mascaras);

  scanf("%s", nome_arquivo);
  getchar();

  imagem = fopen(nome_arquivo,"r");

  if (!imagem) {
    printf("Arquivo não encontrado\n");
    return 1;
  }

  fscanf(imagem, "%s", codigo);
  fscanf(imagem, "%d", &largura);
  fscanf(imagem, "%d", &altura);
  fscanf(imagem, "%d", &nivel_cinza);

  // printf("Código: %s\nLargura: %d\nAltura: %d\nCinza: %d\n", codigo, largura, altura, nivel_cinza);

  matriz = malloc(altura * sizeof(int*));
  for (int i=0; i < altura; i++) {
    matriz[i] = malloc(largura * sizeof(int));
  }

  for (int i=0; i < altura; i++) {
    for (int j=0; j < largura; j++) {
      fscanf(imagem, "%d", &aux);
      matriz[i][j] = aux;
    }
  }

  //Encontrar mascaras na matriz

  fclose(imagem);
  return 0;
}
