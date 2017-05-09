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
  int cor; //0 = branco, 1 = preto
  char** (*gerarMovimentos)(char* tabuleiro);
} rei;

typedef struct {
  int cor; //0 = branco, 1 = preto
  char** (*gerarMovimentos)(char* tabuleiro);
} rainha;

typedef struct {
  int cor; //0 = branco, 1 = preto
  char** (*gerarMovimentos)(char* tabuleiro);
} bispo;

typedef struct {
  int cor; //0 = branco, 1 = preto
  char** (*gerarMovimentos)(char* tabuleiro);
} cavalo;

typedef struct {
  int cor; //0 = branco, 1 = preto
  char** (*gerarMovimentos)(char* tabuleiro);
} torre;

typedef struct {
  int cor; //0 = branco, 1 = preto
  char** (*gerarMovimentos)(char* tabuleiro);
} peao;

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

rei *novoRei (int cor) {
  rei *n_rei;
  n_rei = malloc(sizeof(rei));
  n_rei->cor = cor;
  n_rei->gerarMovimentos = gerarMovimentos_rei;
  return n_rei;
}

rainha *novaRainha (int cor) {
  rainha *n_rainha;
  n_rainha = malloc(sizeof(rainha));
  n_rainha->cor = cor;
  n_rainha->gerarMovimentos = gerarMovimentos_rainha;
  return n_rainha;
}

bispo *novoBispo (int cor) {
  bispo *n_bispo;
  n_bispo = malloc(sizeof(bispo));
  n_bispo->cor = cor;
  n_bispo->gerarMovimentos = gerarMovimentos_bispo;
  return n_bispo;
}

cavalo *novoCavalo (int cor) {
  cavalo *n_cavalo;
  n_cavalo = malloc(sizeof(cavalo));
  n_cavalo->cor = cor;
  n_cavalo->gerarMovimentos = gerarMovimentos_cavalo;
  return n_cavalo;
}

torre *novaTorre (int cor) {
  torre *n_torre;
  n_torre = malloc(sizeof(torre));
  n_torre->cor = cor;
  n_torre->gerarMovimentos = gerarMovimentos_torre;
  return n_torre;
}

peao *novoPeao(int cor) {
  peao *n_peao;
  n_peao = malloc(sizeof(peao));
  n_peao->cor = cor;
  n_peao->gerarMovimentos = gerarMovimentos_peao;
  return n_peao;
}

int main(int argc, char *argv[]) {
  // peao *peaoBranco = novoPeao(1);
  // printf("Cor do peão: %d\n", peaoBranco->cor);
  char inicio[64], turno_cor, roque[4], passant[2];
  int meio_turnos, turnos;

  scanf("%s %c %s %s %d %d", inicio, &turno_cor, roque, passant, &meio_turnos, &turnos);

  // printf("Inicio: %s\nCor do turno: %c\nRoque: %s\nPassant: %s\nMeio turnos: %d\nTurnos: %d\n", inicio, turno_cor, roque, passant, meio_turnos, turnos);

  return 0;
}
