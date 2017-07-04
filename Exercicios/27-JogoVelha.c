/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int checkVictory(char **tabuleiro, int jogador) {
  int cheio = 1;

  for (int i = 0; i < 3; i++) {
    if ((tabuleiro[i][0] == tabuleiro[i][1]) && (tabuleiro[i][1] == tabuleiro[i][2]) && ((tabuleiro[i][0] == 'X') || (tabuleiro[i][0] == 'O'))) {
      printf("%d\n", jogador);
      return 0;
    }
    if ((tabuleiro[0][i] == tabuleiro[1][i]) && (tabuleiro[1][i] == tabuleiro[2][i]) && ((tabuleiro[i][0] == 'X') || (tabuleiro[i][0] == 'O'))) {
      printf("%d\n", jogador);
      return 0;
    }
    if ((tabuleiro[0][0] == tabuleiro[1][1]) && (tabuleiro[1][1] == tabuleiro[2][2]) && ((tabuleiro[i][0] == 'X') || (tabuleiro[i][0] == 'O'))) {
      printf("%d\n", jogador);
      return 0;
    }
    for (int j = 0; j < 3; j++) {
      if ((tabuleiro[i][j] != 'X') && (tabuleiro[i][j] != 'O')) {
        cheio = 0;
        break;
      }
    }
  }
  if (cheio) {
    printf("empate\n");
    return 0;
  }
  return 1;
}

int main(int argc, char *argv[]) {
  char **tabuleiro;
  int linha, coluna, jogador = 1;

  tabuleiro = malloc(3 * sizeof(char*));
  tabuleiro[0] = calloc(3, sizeof(char));
  tabuleiro[1] = calloc(3, sizeof(char));
  tabuleiro[2] = calloc(3, sizeof(char));

  do {
    scanf("%d %d", &linha, &coluna);
    if (jogador == 0) {
      tabuleiro[linha][coluna] = 'X';
      jogador = 1;
    }
    else {
      tabuleiro[linha][coluna] = 'O';
      jogador = 0;
    }
  } while(checkVictory(tabuleiro, jogador));

  return 0;
}
