
/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 18/04/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char Incrementa(char carac) {
  if ((carac != '*') && (carac != '\n')) {
    if (carac == '.') {
      return '1';
    }
    else
    {
      return (char)(((int)(carac - '0')) + 1) + '0';
    }
  }
  return carac;
}

void MontaTabuleiro(char **tabuleiro, int n) {
  for (int k=0; k < n; k++) {
    for (int j=0; j < strlen(tabuleiro[k]); j++) {
      if (tabuleiro[k][j] == '*') {
        if (k > 0) {
          tabuleiro[k-1][j] = Incrementa(tabuleiro[k-1][j]);
          if (j > 0) {
            tabuleiro[k-1][j-1] = Incrementa(tabuleiro[k-1][j-1]);
          }
          if (j < (strlen(tabuleiro[k])-2)) {
            tabuleiro[k-1][j+1] = Incrementa(tabuleiro[k-1][j+1]);
          }
        }
        if (j > 0) {
          tabuleiro[k][j-1] = Incrementa(tabuleiro[k][j-1]);
          if (k < (n-1)) {
            tabuleiro[k+1][j-1] = Incrementa(tabuleiro[k+1][j-1]);
          }
        }
        if (k < (n-1)) {
          tabuleiro[k+1][j] = Incrementa(tabuleiro[k+1][j]);
          if (j < (strlen(tabuleiro[k])-2)) {
            tabuleiro[k+1][j+1] = Incrementa(tabuleiro[k+1][j+1]);
          }
        }
        if (j < (strlen(tabuleiro[k])-2)) {
          tabuleiro[k][j+1] = Incrementa(tabuleiro[k][j+1]);
        }
      }
    }
  }
}

int main(int argc, char *argv[]) {
  char nome_arquivo[20], linha[100], **tabuleiro;
  int opcao, cont, x, y;
  FILE *arquivo;

  scanf("%d", &opcao);

  scanf("%s", nome_arquivo);
  getchar();

  if (opcao == 3) {
    scanf("%d", &x);
    scanf("%d", &y);
  }

  arquivo = fopen(nome_arquivo, "r");
  if (!arquivo) {
    printf("Arquivo não encontrado\n");
    return 1;
  }

  cont = 0;
  tabuleiro = malloc(100 * sizeof(char));
  while (fgets(linha, sizeof linha, arquivo) != NULL) {
    if (opcao == 1) {
      printf("%s", linha);
    }
    else
    {
      tabuleiro[cont] = malloc(strlen(linha) * sizeof(char));
      strcpy(tabuleiro[cont], linha);
      cont++;
    }
  }

  if (opcao == 1) {
    return 0;
  }

  MontaTabuleiro(tabuleiro, cont);

  if ((opcao == 2) || ((opcao == 3) && (tabuleiro[x][y] == '*'))) {
    for (int k=0; k < cont; k++) {
      printf("%s",tabuleiro[k]);
    }
    return 0;
  }

  for (int k=0; k < cont; k++) {
    for (int j=0; j < strlen(tabuleiro[k]); j++) {
      if ((k==x) && (j==y)) {
        printf("%c", tabuleiro[k][j]);
      }
      else {
        printf("X");
      }
    }
    printf("\n");
  }

  return 0;
}
