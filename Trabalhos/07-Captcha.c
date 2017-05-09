/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 18/04/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mks {
  int **mascara;
  int largura;
  int altura;
} mks;

void carregaMascaras(struct mks *mascaras) {
  FILE *masc;
  char nome_arquivo[20], codigo[2];
  int altura, largura, nivel_cinza, aux;

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

    mascaras[i].largura = largura;
    mascaras[i].altura = altura;

    mascaras[i].mascara = malloc(altura * sizeof(int*));
    for (int j=0; j < altura; j++) {
      mascaras[i].mascara[j] = malloc(largura * sizeof(int));
    }

    for (int j=0; j < altura; j++) {
      for (int k=0; k < largura; k++) {
        fscanf(masc, "%d", &aux);
        mascaras[i].mascara[j][k] = aux;
      }
    }

    fclose(masc);
  }
}

int encaixa(struct mks mascaras, int **matriz, int coluna, int linha) {
  int ruido, tolerancia;

  tolerancia = 400;
  ruido = 0;

  for (int i=linha; i < (linha + mascaras.altura); i++) {
    for (int j=coluna; j < (coluna + mascaras.largura); j++) {
      if ((coluna == 71))
        printf("(%d %d %d - %d %d %d)", i-linha, j-coluna, mascaras.mascara[i-linha][j-coluna], i, j, matriz[j][i]);
      if (mascaras.mascara[i-linha][j-coluna] != matriz[j][i]) {
        ruido++;
      }
      if (ruido > tolerancia) {
        return 0;
      }
    }
  }

  return 1;
}

int main(int argc, char *argv[]) {
  FILE *imagem;
  char nome_arquivo[20], codigo[2];
  int **matriz, altura, largura, nivel_cinza, aux;
  struct mks *mascaras;

  mascaras = malloc(10 * sizeof(struct mks));

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

  for (int i=0; i < largura; i++) {
    for (int j=0; j < altura; j++) {
      if (matriz[j][i] == 1) {
        for (int k=0; k <= 9; k++) {
          printf("Tentando encaixar coluna %d e linha %d com %d\n", i, j, k);
          if (encaixa(mascaras[k], matriz, i, j)) {
            printf("%c", k + '0');
          }
        }
      }
    }
  }

  fclose(imagem);
  return 0;
}
