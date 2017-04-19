
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

void MarcaImpressao(char **tabuleiro, int **aux, int x, int y, int n) {
  if ((tabuleiro[x][y] != '\n') && (aux[x][y] == 0)) {
    aux[x][y] = 1;
    if (tabuleiro[x][y] == '.') {
      if (x > 0) {
        if (aux[x-1][y] == 0)
          MarcaImpressao(tabuleiro, aux, x-1, y, n);
        if (y > 0) {
          if (aux[x-1][y-1] == 0)
            MarcaImpressao(tabuleiro, aux, x-1, y-1, n);
        }
        if (y < (strlen(tabuleiro[x])-2)) {
          if (aux[x-1][y+1] == 0)
            MarcaImpressao(tabuleiro, aux, x-1, y+1, n);
        }
      }
      if (y > 0) {
        if (aux[x][y-1] == 0)
          MarcaImpressao(tabuleiro, aux, x, y-1, n);
        if (x < (n-1)) {
          if (aux[x+1][y-1] == 0)
            MarcaImpressao(tabuleiro, aux, x+1, y-1, n);
        }
      }
      if (x < (n-1)) {
        if (aux[x+1][y] == 0)
          MarcaImpressao(tabuleiro, aux, x+1, y, n);
        if (y < (strlen(tabuleiro[x])-2)) {
          if (aux[x+1][y+1] == 0)
            MarcaImpressao(tabuleiro, aux, x+1, y+1, n);
        }
      }
      if (y < (strlen(tabuleiro[x])-2)) {
        if (aux[x][y+1] == 0)
          MarcaImpressao(tabuleiro, aux, x, y+1, n);
      }
    }
  }
}

int main(int argc, char *argv[]) {
  char nome_arquivo[20], linha[100], **tabuleiro;
  int opcao, cont, x, y, **aux;
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
  tabuleiro = malloc(500 * sizeof(char));
  aux = calloc(500, sizeof(int));
  while (fgets(linha, sizeof linha, arquivo) != NULL) {
    if (opcao == 1) {
      printf("%s", linha);
    }
    else
    {
      tabuleiro[cont] = malloc(strlen(linha) * sizeof(char));
      aux[cont] = calloc(strlen(linha), sizeof(int));
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

  if ((opcao == 3) && (tabuleiro[x][y] != '.')) {
    for (int k=0; k < cont; k++) {
      for (int j=0; j < strlen(tabuleiro[k]); j++) {
        if (((k==x) && (j==y)) || (tabuleiro[k][j] == '\n')) {
          printf("%c", tabuleiro[k][j]);
        }
        else {
          printf("X");
        }
      }
    }
  }
  else {
    MarcaImpressao(tabuleiro, aux, x, y, cont);
    for (int k=0; k < cont; k++) {
      for (int j=0; j < strlen(tabuleiro[k]); j++) {
        if ((aux[k][j] == 1) || (tabuleiro[k][j] == '\n')) {
          printf("%c", tabuleiro[k][j]);
        }
        else {
          printf("X");
        }
      }
    }
  }

  return 0;
}
