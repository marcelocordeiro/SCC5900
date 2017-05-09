/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 09/05/2017

O algoritmo procura por bits 1 na imagem, e então inicia uma comparação com as máscaras de cada número, considerando um fator de tolerância para eliminar os ruídos.
Para que o método funcione, todas as máscaras precisam ter o número justificado ao lado esquerdo da máscara, por isso a máscara do número 1 é inicializada manualmente, pois no arquivo ele se encontra centralizado.
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

    if (i == 1) {
      largura = 20;
    }

    mascaras[i].largura = largura;
    mascaras[i].altura = altura;

    mascaras[i].mascara = malloc(altura * sizeof(int*));
    for (int j=0; j < altura; j++) {
      mascaras[i].mascara[j] = malloc(largura * sizeof(int));
    }

    for (int j=0; j < altura; j++) {
      for (int k=0; k < largura; k++) {
        if (i != 1)
        {
          fscanf(masc, "%d", &aux);
          mascaras[i].mascara[j][k] = aux;
        }
        else
        {
          if (k <= 9) {
            mascaras[i].mascara[j][k] = 1;
          }
          else
          {
            mascaras[i].mascara[j][k] = 0;
          }
        }
      }
    }

    fclose(masc);
  }
}

int encaixa(struct mks mascaras, int **matriz, int largura, int altura, int coluna, int linha) {
  int ruido, tolerancia, i, j;

  tolerancia = 100;
  ruido = 0;

  for (i=linha; ((i < (linha + mascaras.altura)) && (i < altura)); i++) {
    for (j=coluna; ((j < (coluna + mascaras.largura)) && (j < largura)); j++) {
      if (mascaras.mascara[i-linha][j-coluna] != matriz[i][j]) {
        ruido++;
      }
      if (ruido > tolerancia) {
        return 0;
      }
    }
  }
  if ((i == linha + mascaras.altura) && (j == coluna + mascaras.largura))
  {
    return 1;
  }

  return 0;
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
          if (encaixa(mascaras[k], matriz, largura, altura, i, j)) {
            printf("%c", k + '0');
            i += mascaras[k].largura;
            j = altura;
            break;
          }
        }
      }
    }
  }

  fclose(imagem);
  return 0;
}
