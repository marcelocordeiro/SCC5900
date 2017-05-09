/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 09/05/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int cor, linha, coluna; //Cor: 0 = branco, 1 = preto
  char** (*gerarMovimentos)(char* tabuleiro);
} rei;

typedef struct {
  int cor, linha, coluna; //Cor: 0 = branco, 1 = preto
  char** (*gerarMovimentos)(char* tabuleiro);
} rainha;

typedef struct {
  int cor, linha, coluna; //Cor: 0 = branco, 1 = preto
  char** (*gerarMovimentos)(char* tabuleiro);
} bispo;

typedef struct {
  int cor, linha, coluna; //Cor: 0 = branco, 1 = preto
  char** (*gerarMovimentos)(char* tabuleiro);
} cavalo;

typedef struct {
  int cor, linha, coluna; //Cor: 0 = branco, 1 = preto
  char** (*gerarMovimentos)(char* tabuleiro);
} torre;

typedef struct {
  int cor, linha, coluna; //Cor: 0 = branco, 1 = preto
  char** (*gerarMovimentos)(char* tabuleiro);
} peao;

typedef struct {
  rei **v_rei;
  rainha **v_rainha;
  bispo **v_bispo;
  cavalo **v_cavalo;
  torre **v_torre;
  peao **v_peao;
  char printable[8][8];
  int c_rei, c_rainha, c_bispo, c_cavalo, c_torre, c_peao;
} pecas;

char **gerarMovimentos_rei (char *tabuleiro) {

}

char **gerarMovimentos_rainha (char *tabuleiro) {

}

char **gerarMovimentos_bispo (char *tabuleiro) {

}

char **gerarMovimentos_cavalo (char *tabuleiro) {

}

char **gerarMovimentos_torre (char *tabuleiro) {

}

char **gerarMovimentos_peao (char *tabuleiro) {

}

rei *novoRei (int cor, int linha, int coluna) {
  rei *n_rei;
  n_rei = malloc(sizeof(rei));
  n_rei->cor = cor;
  n_rei->linha = linha;
  n_rei->coluna = coluna;
  n_rei->gerarMovimentos = gerarMovimentos_rei;
  return n_rei;
}

rainha *novaRainha (int cor, int linha, int coluna) {
  rainha *n_rainha;
  n_rainha = malloc(sizeof(rainha));
  n_rainha->cor = cor;
  n_rainha->linha = linha;
  n_rainha->coluna = coluna;
  n_rainha->gerarMovimentos = gerarMovimentos_rainha;
  return n_rainha;
}

bispo *novoBispo (int cor, int linha, int coluna) {
  bispo *n_bispo;
  n_bispo = malloc(sizeof(bispo));
  n_bispo->cor = cor;
  n_bispo->linha = linha;
  n_bispo->coluna = coluna;
  n_bispo->gerarMovimentos = gerarMovimentos_bispo;
  return n_bispo;
}

cavalo *novoCavalo (int cor, int linha, int coluna) {
  cavalo *n_cavalo;
  n_cavalo = malloc(sizeof(cavalo));
  n_cavalo->cor = cor;
  n_cavalo->linha = linha;
  n_cavalo->coluna = coluna;
  n_cavalo->gerarMovimentos = gerarMovimentos_cavalo;
  return n_cavalo;
}

torre *novaTorre (int cor, int linha, int coluna) {
  torre *n_torre;
  n_torre = malloc(sizeof(torre));
  n_torre->cor = cor;
  n_torre->linha = linha;
  n_torre->coluna = coluna;
  n_torre->gerarMovimentos = gerarMovimentos_torre;
  return n_torre;
}

peao *novoPeao(int cor, int linha, int coluna) {
  peao *n_peao;
  n_peao = malloc(sizeof(peao));
  n_peao->cor = cor;
  n_peao->linha = linha;
  n_peao->coluna = coluna;
  n_peao->gerarMovimentos = gerarMovimentos_peao;
  return n_peao;
}

pecas *iniciaTabuleiro(char *inicio) {
  pecas *tabuleiro;
  int linha = 0, coluna = 0, aux;

  tabuleiro = malloc(sizeof(pecas));
  tabuleiro->v_rei = malloc(sizeof(rei*));
  tabuleiro->v_rainha = malloc(sizeof(rainha*));
  tabuleiro->v_bispo = malloc(sizeof(bispo*));
  tabuleiro->v_cavalo = malloc(sizeof(cavalo*));
  tabuleiro->v_torre = malloc(sizeof(torre*));
  tabuleiro->v_peao = malloc(sizeof(peao*));

  tabuleiro->c_rei = 0;
  tabuleiro->c_rainha = 0;
  tabuleiro->c_bispo = 0;
  tabuleiro->c_cavalo = 0;
  tabuleiro->c_torre = 0;
  tabuleiro->c_peao = 0;

  for (int i=0; i < strlen(inicio); i++) {
    tabuleiro->printable[linha][coluna] = inicio[i];
    switch (inicio[i]) {
      case 'K':
        tabuleiro->c_rei++;
        tabuleiro->v_rei = realloc(tabuleiro->v_rei, tabuleiro->c_rei * sizeof(rei));
        tabuleiro->v_rei[tabuleiro->c_rei - 1] = novoRei(0, linha, coluna);
        coluna++;
        break;
      case 'k':
        tabuleiro->c_rei++;
        tabuleiro->v_rei = realloc(tabuleiro->v_rei, tabuleiro->c_rei * sizeof(rei));
        tabuleiro->v_rei[tabuleiro->c_rei - 1] = novoRei(1, linha, coluna);
        coluna++;
        break;
      case 'Q':
        tabuleiro->c_rainha++;
        tabuleiro->v_rainha = realloc(tabuleiro->v_rainha, tabuleiro->c_rainha * sizeof(rainha));
        tabuleiro->v_rainha[tabuleiro->c_rainha - 1] = novaRainha(0, linha, coluna);
        coluna++;
        break;
      case 'q':
        tabuleiro->c_rainha++;
        tabuleiro->v_rainha = realloc(tabuleiro->v_rainha, tabuleiro->c_rainha * sizeof(rainha));
        tabuleiro->v_rainha[tabuleiro->c_rainha - 1] = novaRainha(1, linha, coluna);
        coluna++;
        break;
      case 'B':
        tabuleiro->c_bispo++;
        tabuleiro->v_bispo = realloc(tabuleiro->v_bispo, tabuleiro->c_bispo * sizeof(bispo));
        tabuleiro->v_bispo[tabuleiro->c_bispo - 1] = novoBispo(0, linha, coluna);
        coluna++;
        break;
      case 'b':
        tabuleiro->c_bispo++;
        tabuleiro->v_bispo = realloc(tabuleiro->v_bispo, tabuleiro->c_bispo * sizeof(bispo));
        tabuleiro->v_bispo[tabuleiro->c_bispo - 1] = novoBispo(1, linha, coluna);
        coluna++;
        break;
      case 'N':
        tabuleiro->c_cavalo++;
        tabuleiro->v_cavalo = realloc(tabuleiro->v_cavalo, tabuleiro->c_cavalo * sizeof(cavalo));
        tabuleiro->v_cavalo[tabuleiro->c_cavalo - 1] = novoCavalo(0, linha, coluna);
        coluna++;
        break;
      case 'n':
        tabuleiro->c_cavalo++;
        tabuleiro->v_cavalo = realloc(tabuleiro->v_cavalo, tabuleiro->c_cavalo * sizeof(cavalo));
        tabuleiro->v_cavalo[tabuleiro->c_cavalo - 1] = novoCavalo(1, linha, coluna);
        coluna++;
        break;
      case 'R':
        tabuleiro->c_torre++;
        tabuleiro->v_torre = realloc(tabuleiro->v_torre, tabuleiro->c_torre * sizeof(torre));
        tabuleiro->v_torre[tabuleiro->c_torre - 1] = novaTorre(0, linha, coluna);
        coluna++;
        break;
      case 'r':
        tabuleiro->c_torre++;
        tabuleiro->v_torre = realloc(tabuleiro->v_torre, tabuleiro->c_torre * sizeof(torre));
        tabuleiro->v_torre[tabuleiro->c_torre - 1] = novaTorre(1, linha, coluna);
        coluna++;
        break;
      case 'P':
        tabuleiro->c_peao++;
        tabuleiro->v_peao = realloc(tabuleiro->v_peao, tabuleiro->c_peao * sizeof(peao));
        tabuleiro->v_peao[tabuleiro->c_peao - 1] = novoPeao(0, linha, coluna);
        coluna++;
        break;
      case 'p':
        tabuleiro->c_peao++;
        tabuleiro->v_peao = realloc(tabuleiro->v_peao, tabuleiro->c_peao * sizeof(peao));
        tabuleiro->v_peao[tabuleiro->c_peao - 1] = novoPeao(1, linha, coluna);
        coluna++;
        break;
      case '/':
        linha++;
        coluna = 0;
        break;
      default:
        aux = (int)(inicio[i] - '0');
        for (int j=coluna; j <= (coluna + aux); j++) {
          tabuleiro->printable[linha][j] = '-';
        }
        coluna += aux;
        break;
    }
  }

  return tabuleiro;
}

void printTabuleiro(pecas *tabuleiro) {
  for (int i=0; i < 8; i++) {
    for (int j=0; j < 8; j++) {
      printf("%c ", tabuleiro->printable[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  pecas *tabuleiro;
  char inicio[64], turno_cor, roque[4], passant[2];
  int meio_turnos, turnos;

  scanf("%s %c %s %s %d %d", inicio, &turno_cor, roque, passant, &meio_turnos, &turnos);

  // printf("Inicio: %s\nCor do turno: %c\nRoque: %s\nPassant: %s\nMeio turnos: %d\nTurnos: %d\n", inicio, turno_cor, roque, passant, meio_turnos, turnos);

  tabuleiro = iniciaTabuleiro(inicio);

  printTabuleiro(tabuleiro);

  return 0;
}
