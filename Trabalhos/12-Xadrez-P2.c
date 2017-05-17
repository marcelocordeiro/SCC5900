/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 16/05/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int cor, linha, coluna, move; //Cor: 0 = branco, 1 = preto
} rei;

typedef struct {
  int cor, linha, coluna, move; //Cor: 0 = branco, 1 = preto
} rainha;

typedef struct {
  int cor, linha, coluna, move; //Cor: 0 = branco, 1 = preto
} bispo;

typedef struct {
  int cor, linha, coluna, move; //Cor: 0 = branco, 1 = preto
} cavalo;

typedef struct {
  int cor, linha, coluna, move; //Cor: 0 = branco, 1 = preto
} torre;

typedef struct {
  int cor, linha, coluna, move; //Cor: 0 = branco, 1 = preto
} peao;

typedef struct {
  rei *rei_br, *rei_pr;
  rainha *rainha_br, *rainha_pr;
  bispo **bispos_br, **bispos_pr;
  cavalo **cavalos_br, **cavalos_pr;
  torre **torres_br, **torres_pr;
  peao **peoes_br, **peoes_pr;
  char printable[8][8];
  //Contadores de quantas peças de cada cor existem no jogo
  int c_rei_pr, c_rei_br, c_rainha_pr, c_rainha_br, c_bispo_pr, c_bispo_br, c_cavalo_pr, c_cavalo_br, c_torre_pr, c_torre_br, c_peao_pr, c_peao_br;
  int cont_roque_pr, cont_roque_br;
} pecas;

rei *novoRei (int cor, int linha, int coluna) {
  rei *n_rei;
  n_rei = malloc(sizeof(rei));
  n_rei->cor = cor;
  n_rei->linha = linha;
  n_rei->coluna = coluna;
  n_rei->move = 0;
  return n_rei;
}

rainha *novaRainha (int cor, int linha, int coluna) {
  rainha *n_rainha;
  n_rainha = malloc(sizeof(rainha));
  n_rainha->cor = cor;
  n_rainha->linha = linha;
  n_rainha->coluna = coluna;
  n_rainha->move = 0;
  return n_rainha;
}

bispo *novoBispo (int cor, int linha, int coluna) {
  bispo *n_bispo;
  n_bispo = malloc(sizeof(bispo));
  n_bispo->cor = cor;
  n_bispo->linha = linha;
  n_bispo->coluna = coluna;
  n_bispo->move = 0;
  return n_bispo;
}

cavalo *novoCavalo (int cor, int linha, int coluna) {
  cavalo *n_cavalo;
  n_cavalo = malloc(sizeof(cavalo));
  n_cavalo->cor = cor;
  n_cavalo->linha = linha;
  n_cavalo->coluna = coluna;
  n_cavalo->move = 0;
  return n_cavalo;
}

torre *novaTorre (int cor, int linha, int coluna) {
  torre *n_torre;
  n_torre = malloc(sizeof(torre));
  n_torre->cor = cor;
  n_torre->linha = linha;
  n_torre->coluna = coluna;
  n_torre->move = 0;
  return n_torre;
}

peao *novoPeao(int cor, int linha, int coluna) {
  peao *n_peao;
  n_peao = malloc(sizeof(peao));
  n_peao->cor = cor;
  n_peao->linha = linha;
  n_peao->coluna = coluna;
  n_peao->move = 0;
  return n_peao;
}

pecas *iniciaTabuleiro(char *inicio) {
  pecas *tabuleiro;
  int linha = 0, coluna = 0, aux;

  tabuleiro = malloc(sizeof(pecas));
  tabuleiro->rei_br = malloc(sizeof(rei*));
  tabuleiro->rei_pr = malloc(sizeof(rei*));
  tabuleiro->rainha_br = malloc(sizeof(rainha*));
  tabuleiro->rainha_pr = malloc(sizeof(rainha*));
  tabuleiro->bispos_br = malloc(sizeof(bispo*));
  tabuleiro->bispos_pr = malloc(sizeof(bispo*));
  tabuleiro->cavalos_br = malloc(sizeof(cavalo*));
  tabuleiro->cavalos_pr = malloc(sizeof(cavalo*));
  tabuleiro->torres_br = malloc(sizeof(torre*));
  tabuleiro->torres_pr = malloc(sizeof(torre*));
  tabuleiro->peoes_br = malloc(sizeof(peao*));
  tabuleiro->peoes_pr = malloc(sizeof(peao*));

  tabuleiro->c_rei_br = 0;
  tabuleiro->c_rei_pr = 0;
  tabuleiro->c_rainha_br = 0;
  tabuleiro->c_rainha_pr = 0;
  tabuleiro->c_bispo_br = 0;
  tabuleiro->c_bispo_pr = 0;
  tabuleiro->c_cavalo_br = 0;
  tabuleiro->c_cavalo_pr = 0;
  tabuleiro->c_torre_br = 0;
  tabuleiro->c_torre_pr = 0;
  tabuleiro->c_peao_br = 0;
  tabuleiro->c_peao_pr = 0;

  for (int i=0; i < strlen(inicio); i++) {
    tabuleiro->printable[linha][coluna] = inicio[i];
    switch (inicio[i]) {
      case 'K':
        tabuleiro->c_rei_br++;
        tabuleiro->rei_br = realloc(tabuleiro->rei_br, tabuleiro->c_rei_br * sizeof(rei));
        tabuleiro->rei_br = novoRei(0, linha, coluna);
        if ((linha != 7) || (coluna != 4)) {
          tabuleiro->cont_roque_br = 1;
        }
        else {
          tabuleiro->cont_roque_br = 0;
        }
        coluna++;
        break;
      case 'k':
        tabuleiro->c_rei_pr++;
        tabuleiro->rei_pr = realloc(tabuleiro->rei_pr, tabuleiro->c_rei_pr * sizeof(rei));
        tabuleiro->rei_pr = novoRei(1, linha, coluna);
        if ((linha != 0) || (coluna != 4)) {
          tabuleiro->cont_roque_pr = 1;
        }
        else {
          tabuleiro->cont_roque_pr = 0;
        }
        coluna++;
        break;
      case 'Q':
        tabuleiro->c_rainha_br++;
        tabuleiro->rainha_br = realloc(tabuleiro->rainha_br, tabuleiro->c_rainha_br * sizeof(rainha));
        tabuleiro->rainha_br = novaRainha(0, linha, coluna);
        coluna++;
        break;
      case 'q':
        tabuleiro->c_rainha_pr++;
        tabuleiro->rainha_pr = realloc(tabuleiro->rainha_pr, tabuleiro->c_rainha_pr * sizeof(rainha));
        tabuleiro->rainha_pr = novaRainha(1, linha, coluna);
        coluna++;
        break;
      case 'B':
        tabuleiro->c_bispo_br++;
        tabuleiro->bispos_br = realloc(tabuleiro->bispos_br, tabuleiro->c_bispo_br * sizeof(bispo));
        tabuleiro->bispos_br[tabuleiro->c_bispo_br - 1] = novoBispo(0, linha, coluna);
        coluna++;
        break;
      case 'b':
        tabuleiro->c_bispo_pr++;
        tabuleiro->bispos_pr = realloc(tabuleiro->bispos_pr, tabuleiro->c_bispo_pr * sizeof(bispo));
        tabuleiro->bispos_pr[tabuleiro->c_bispo_pr - 1] = novoBispo(1, linha, coluna);
        coluna++;
        break;
      case 'N':
        tabuleiro->c_cavalo_br++;
        tabuleiro->cavalos_br = realloc(tabuleiro->cavalos_br, tabuleiro->c_cavalo_br * sizeof(cavalo));
        tabuleiro->cavalos_br[tabuleiro->c_cavalo_br - 1] = novoCavalo(0, linha, coluna);
        coluna++;
        break;
      case 'n':
        tabuleiro->c_cavalo_pr++;
        tabuleiro->cavalos_pr = realloc(tabuleiro->cavalos_pr, tabuleiro->c_cavalo_pr * sizeof(cavalo));
        tabuleiro->cavalos_pr[tabuleiro->c_cavalo_pr - 1] = novoCavalo(1, linha, coluna);
        coluna++;
        break;
      case 'R':
        tabuleiro->c_torre_br++;
        tabuleiro->torres_br = realloc(tabuleiro->torres_br, tabuleiro->c_torre_br * sizeof(torre));
        tabuleiro->torres_br[tabuleiro->c_torre_br - 1] = novaTorre(0, linha, coluna);
        if ((linha != 7) || ((coluna != 0) && (coluna != 7))) {
          tabuleiro->cont_roque_br = 1;
        }
        else {
          tabuleiro->cont_roque_br = 0;
        }
        coluna++;
        break;
      case 'r':
        tabuleiro->c_torre_pr++;
        tabuleiro->torres_pr = realloc(tabuleiro->torres_pr, tabuleiro->c_torre_pr * sizeof(torre));
        tabuleiro->torres_pr[tabuleiro->c_torre_pr - 1] = novaTorre(1, linha, coluna);
        if ((linha != 7) || ((coluna != 0) && (coluna != 7))) {
          tabuleiro->cont_roque_pr = 1;
        }
        else {
          tabuleiro->cont_roque_pr = 0;
        }
        coluna++;
        break;
      case 'P':
        tabuleiro->c_peao_br++;
        tabuleiro->peoes_br = realloc(tabuleiro->peoes_br, tabuleiro->c_peao_br * sizeof(peao));
        tabuleiro->peoes_br[tabuleiro->c_peao_br - 1] = novoPeao(0, linha, coluna);
        coluna++;
        break;
      case 'p':
        tabuleiro->c_peao_pr++;
        tabuleiro->peoes_pr = realloc(tabuleiro->peoes_pr, tabuleiro->c_peao_pr * sizeof(peao));
        tabuleiro->peoes_pr[tabuleiro->c_peao_pr - 1] = novoPeao(1, linha, coluna);
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

void printFEN(pecas *tabuleiro, char turno_cor, int meio_turnos, int turnos) {
  int cont;

  for (int i=0; i < 8; i++) {
    for (int j=0; j < 8; j++) {
      if (tabuleiro->printable[i][j] != '-') {
        printf("%c", tabuleiro->printable[i][j]);
      }
      else {
        cont = 0;
        while ((tabuleiro->printable[i][j] == '-') && (j < 8)) {
          cont++;
          j++;
        }
        j--;
        printf("%d", cont);
      }
    }
    if (i < 7) {
      printf("/");
    }
  }

  printf(" %c ", turno_cor);

  if (((tabuleiro->cont_roque_pr == 1) && (tabuleiro->cont_roque_br == 1)) || //Os dois jogadores já fizeram roque
     ((tabuleiro->c_torre_pr == 0) && (tabuleiro->c_torre_br == 0)) || //Não existem mais torres na partida
     ((tabuleiro->rei_br->move > 0) || (tabuleiro->rei_pr->move > 0))) { //Os dois reis já foram movidos
    printf("-");
  }
  else {
    switch (tabuleiro->c_torre_pr) {
      case 1:
        switch (tabuleiro->c_torre_br) {
          case 1:
              if ((tabuleiro->torres_pr[0]->move > 0) && (tabuleiro->torres_br[0]->move > 0)) {
                printf("-");
                break;
              }
            break;
          case 2:
            if ((tabuleiro->torres_pr[0]->move > 0) && (tabuleiro->torres_br[0]->move > 0) && (tabuleiro->torres_br[1]->move > 0)) {
              printf("-");
              break;
            }
            break;
        }
        break;
      case 2:
        switch (tabuleiro->c_torre_br) {
          case 1:
              if ((tabuleiro->torres_pr[0]->move > 0) && (tabuleiro->torres_pr[1]->move > 0) && (tabuleiro->torres_br[0]->move > 0)) {
                printf("-");
                break;
              }
            break;
          case 2:
            if ((tabuleiro->torres_pr[0]->move > 0) && (tabuleiro->torres_pr[1]->move > 0) && (tabuleiro->torres_br[0]->move > 0) && (tabuleiro->torres_br[1]->move > 0)) {
              printf("-");
              break;
            }
            break;
        }
        break;
    }
  }

  printf(" ");

  printf("-");

  printf(" %d", meio_turnos);
  printf(" %d\n", turnos);
}

int faltaMaterial(pecas *tabuleiro) {
  int soma;

  soma = tabuleiro->c_rainha_pr + tabuleiro->c_rainha_br + tabuleiro->c_bispo_pr + tabuleiro->c_bispo_br + tabuleiro->c_cavalo_pr + tabuleiro->c_cavalo_br + tabuleiro->c_torre_pr + tabuleiro->c_torre_br + tabuleiro->c_peao_pr + tabuleiro->c_peao_br;

  if (soma == 0) {
    return 1;
  }
  else {
    if (soma == 1) {
      if ((tabuleiro->c_bispo_pr == 1) || (tabuleiro->c_bispo_br == 1) || (tabuleiro->c_cavalo_pr == 1) || (tabuleiro->c_cavalo_br == 1)) {
        return 1;
      }
    }
  }

  return 0;
}

int executaMovimento(pecas **tabuleiro, char *movimento) {
  int linha_origem, coluna_origem, linha_destino, coluna_destino, comeu = 0;

  coluna_origem = movimento[0] - 'a';
  linha_origem = abs((movimento[1] - '0') - 8);
  coluna_destino = movimento[2] - 'a';
  linha_destino = abs((movimento[3] - '0') - 8);

  if ((*tabuleiro)->printable[linha_destino][coluna_destino] != '-') {
    comeu = 1;
    switch ((*tabuleiro)->printable[linha_destino][coluna_destino]) {
      case 'Q':
        (*tabuleiro)->c_rainha_br--;
        break;
      case 'q':
        (*tabuleiro)->c_rainha_pr--;
        break;
      case 'B':
        for (int i=0; i < (*tabuleiro)->c_bispo_br; i++) {
          if (((*tabuleiro)->bispos_br[i]->linha == linha_destino) && ((*tabuleiro)->bispos_br[i]->coluna == coluna_destino)) {
            for (int j=(i+1); j < (*tabuleiro)->c_bispo_br; j++) {
              (*tabuleiro)->bispos_br[i] = (*tabuleiro)->bispos_br[j];
            }
          }
          break;
        }
        (*tabuleiro)->c_bispo_br--;
        break;
      case 'b':
        for (int i=0; i < (*tabuleiro)->c_bispo_pr; i++) {
          if (((*tabuleiro)->bispos_pr[i]->linha == linha_destino) && ((*tabuleiro)->bispos_pr[i]->coluna == coluna_destino)) {
            for (int j=(i+1); j < (*tabuleiro)->c_bispo_pr; j++) {
              (*tabuleiro)->bispos_pr[i] = (*tabuleiro)->bispos_pr[j];
            }
          }
          break;
        }
        (*tabuleiro)->c_bispo_pr--;
        break;
      case 'N':
        for (int i=0; i < (*tabuleiro)->c_cavalo_br; i++) {
          if (((*tabuleiro)->cavalos_br[i]->linha == linha_destino) && ((*tabuleiro)->cavalos_br[i]->coluna == coluna_destino)) {
            for (int j=(i+1); j < (*tabuleiro)->c_cavalo_br; j++) {
              (*tabuleiro)->cavalos_br[i] = (*tabuleiro)->cavalos_br[j];
            }
          }
          break;
        }
        (*tabuleiro)->c_cavalo_br--;
        break;
      case 'n':
        for (int i=0; i < (*tabuleiro)->c_cavalo_pr; i++) {
          if (((*tabuleiro)->cavalos_pr[i]->linha == linha_destino) && ((*tabuleiro)->cavalos_pr[i]->coluna == coluna_destino)) {
            for (int j=(i+1); j < (*tabuleiro)->c_cavalo_pr; j++) {
              (*tabuleiro)->cavalos_pr[i] = (*tabuleiro)->cavalos_pr[j];
            }
          }
          break;
        }
        (*tabuleiro)->c_cavalo_pr--;
        break;
      case 'R':
        for (int i=0; i < (*tabuleiro)->c_torre_br; i++) {
          if (((*tabuleiro)->torres_br[i]->linha == linha_destino) && ((*tabuleiro)->torres_br[i]->coluna == coluna_destino)) {
            for (int j=(i+1); j < (*tabuleiro)->c_torre_br; j++) {
              (*tabuleiro)->torres_br[i] = (*tabuleiro)->torres_br[j];
            }
          }
          break;
        }
        (*tabuleiro)->c_torre_br--;
        break;
      case 'r':
        for (int i=0; i < (*tabuleiro)->c_torre_pr; i++) {
          if (((*tabuleiro)->torres_pr[i]->linha == linha_destino) && ((*tabuleiro)->torres_pr[i]->coluna == coluna_destino)) {
            for (int j=(i+1); j < (*tabuleiro)->c_torre_pr; j++) {
              (*tabuleiro)->torres_pr[i] = (*tabuleiro)->torres_pr[j];
            }
          }
          break;
        }
        (*tabuleiro)->c_torre_pr--;
        break;
      case 'P':
        for (int i=0; i < (*tabuleiro)->c_peao_br; i++) {
          if (((*tabuleiro)->peoes_br[i]->linha == linha_destino) && ((*tabuleiro)->peoes_br[i]->coluna == coluna_destino)) {
            for (int j=(i+1); j < (*tabuleiro)->c_peao_br; j++) {
              (*tabuleiro)->peoes_br[i] = (*tabuleiro)->peoes_br[j];
            }
          }
          break;
        }
        (*tabuleiro)->c_peao_br--;
        break;
      case 'p':
        for (int i=0; i < (*tabuleiro)->c_peao_pr; i++) {
          if (((*tabuleiro)->peoes_pr[i]->linha == linha_destino) && ((*tabuleiro)->peoes_pr[i]->coluna == coluna_destino)) {
            for (int j=(i+1); j < (*tabuleiro)->c_peao_pr; j++) {
              (*tabuleiro)->peoes_pr[i] = (*tabuleiro)->peoes_pr[j];
            }
          }
          break;
        }
        (*tabuleiro)->c_peao_pr--;
        break;
      case '-':
        printf("Movimento invalido. Tente novamente.\n");
        return 0;
    }
  }

  switch ((*tabuleiro)->printable[linha_origem][coluna_origem]) {
    case 'K':
      (*tabuleiro)->rei_br->linha = linha_destino;
      (*tabuleiro)->rei_br->coluna = coluna_destino;
      (*tabuleiro)->rei_br->move++;
      break;
    case 'k':
      (*tabuleiro)->rei_pr->linha = linha_destino;
      (*tabuleiro)->rei_pr->coluna = coluna_destino;
      (*tabuleiro)->rei_pr->move++;
      break;
    case 'Q':
      (*tabuleiro)->rainha_br->linha = linha_destino;
      (*tabuleiro)->rainha_br->coluna = coluna_destino;
      (*tabuleiro)->rainha_br->move++;
      break;
    case 'q':
      (*tabuleiro)->rainha_pr->linha = linha_destino;
      (*tabuleiro)->rainha_pr->coluna = coluna_destino;
      (*tabuleiro)->rainha_pr->move++;
      break;
    case 'B':
      for (int i=0; i < (*tabuleiro)->c_bispo_br; i++) {
        if (((*tabuleiro)->bispos_br[i]->linha == linha_origem) && ((*tabuleiro)->bispos_br[i]->coluna == coluna_origem)) {
          (*tabuleiro)->bispos_br[i]->linha = linha_destino;
          (*tabuleiro)->bispos_br[i]->coluna = coluna_destino;
          (*tabuleiro)->bispos_br[i]->move++;
          break;
        }
      }
      break;
    case 'b':
      for (int i=0; i < (*tabuleiro)->c_bispo_pr; i++) {
        if (((*tabuleiro)->bispos_pr[i]->linha == linha_origem) && ((*tabuleiro)->bispos_pr[i]->coluna == coluna_origem)) {
          (*tabuleiro)->bispos_pr[i]->linha = linha_destino;
          (*tabuleiro)->bispos_pr[i]->coluna = coluna_destino;
          (*tabuleiro)->bispos_pr[i]->move++;
          break;
        }
      }
      break;
    case 'N':
      for (int i=0; i < (*tabuleiro)->c_cavalo_br; i++) {
        if (((*tabuleiro)->cavalos_br[i]->linha == linha_origem) && ((*tabuleiro)->cavalos_br[i]->coluna == coluna_origem)) {
          (*tabuleiro)->cavalos_br[i]->linha = linha_destino;
          (*tabuleiro)->cavalos_br[i]->coluna = coluna_destino;
          (*tabuleiro)->cavalos_br[i]->move++;
          break;
        }
      }
      break;
    case 'n':
      for (int i=0; i < (*tabuleiro)->c_cavalo_pr; i++) {
        if (((*tabuleiro)->cavalos_pr[i]->linha == linha_origem) && ((*tabuleiro)->cavalos_pr[i]->coluna == coluna_origem)) {
          (*tabuleiro)->cavalos_pr[i]->linha = linha_destino;
          (*tabuleiro)->cavalos_pr[i]->coluna = coluna_destino;
          (*tabuleiro)->cavalos_pr[i]->move++;
          break;
        }
      }
      break;
    case 'R':
      for (int i=0; i < (*tabuleiro)->c_torre_br; i++) {
        if (((*tabuleiro)->torres_br[i]->linha == linha_origem) && ((*tabuleiro)->torres_br[i]->coluna == coluna_origem)) {
          (*tabuleiro)->torres_br[i]->linha = linha_destino;
          (*tabuleiro)->torres_br[i]->coluna = coluna_destino;
          (*tabuleiro)->torres_br[i]->move++;
          break;
        }
      }
      break;
    case 'r':
      for (int i=0; i < (*tabuleiro)->c_torre_pr; i++) {
        if (((*tabuleiro)->torres_pr[i]->linha == linha_origem) && ((*tabuleiro)->torres_pr[i]->coluna == coluna_origem)) {
          (*tabuleiro)->torres_pr[i]->linha = linha_destino;
          (*tabuleiro)->torres_pr[i]->coluna = coluna_destino;
          (*tabuleiro)->torres_pr[i]->move++;
          break;
        }
      }
      break;
    case 'P':
      for (int i=0; i < (*tabuleiro)->c_peao_br; i++) {
        if (((*tabuleiro)->peoes_br[i]->linha == linha_origem) && ((*tabuleiro)->peoes_br[i]->coluna == coluna_origem)) {
          (*tabuleiro)->peoes_br[i]->linha = linha_destino;
          (*tabuleiro)->peoes_br[i]->coluna = coluna_destino;
          (*tabuleiro)->peoes_br[i]->move++;
          break;
        }
      }
      break;
    case 'p':
      for (int i=0; i < (*tabuleiro)->c_peao_pr; i++) {
        if (((*tabuleiro)->peoes_pr[i]->linha == linha_origem) && ((*tabuleiro)->peoes_pr[i]->coluna == coluna_origem)) {
          (*tabuleiro)->peoes_pr[i]->linha = linha_destino;
          (*tabuleiro)->peoes_pr[i]->coluna = coluna_destino;
          (*tabuleiro)->peoes_pr[i]->move++;
          break;
        }
      }
      break;
    case '-':
      printf("Movimento invalido. Tente novamente.\n");
      return 0;
  }

  (*tabuleiro)->printable[linha_destino][coluna_destino] = (*tabuleiro)->printable[linha_origem][coluna_origem];
  (*tabuleiro)->printable[linha_origem][coluna_origem] = '-';

  return comeu;
}

int main(int argc, char *argv[]) {
  pecas *tabuleiro;
  char inicio[64], turno_cor, roque[4], passant[2], movimento[5];
  int meio_turnos, turnos, game = 1;

  scanf("%s %c %s %s %d %d", inicio, &turno_cor, roque, passant, &meio_turnos, &turnos);

  tabuleiro = iniciaTabuleiro(inicio);

  do {
    printFEN(tabuleiro, turno_cor, meio_turnos, turnos);

    if (meio_turnos >= 50) {
      printf("Empate -- Regra dos 50 Movimentos\n");
      game = 0;
      break;
    }

    if (faltaMaterial(tabuleiro)) {
      printf("Empate -- Falta de Material\n");
      game = 0;
      break;
    }

    scanf("%s", movimento);

    if (turno_cor == 'w') {
      turno_cor = 'b';
    }
    else {
      turno_cor = 'w';
      turnos++;
    }

    if (executaMovimento(&tabuleiro, movimento) == 0) {
      meio_turnos++;
    }
    else {
      meio_turnos = 0;
    }

  } while (game);

  return 0;
}
