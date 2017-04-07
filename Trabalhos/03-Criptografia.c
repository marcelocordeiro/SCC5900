/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/04/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void MontaTabela(char tabela[]) {
  for (int i=1; i <= 26; i++) {
    tabela[i] = (char) i + 96;
  }
  for (int i=27; i <= 52; i++) {
    tabela[i] = (char) i + 38;
  }
  for (int i=53; i <= 69; i++) {
    tabela[i] = (char) i - 5;
  }
  for (int i=70; i <= 84; i++) {
    tabela[i] = (char) i - 37;
  }
  tabela[0] = ' ';
  tabela[85] = '[';
  tabela[86] = '\\';
  tabela[87] = ']';
  tabela[88] = '_';
  tabela[89] = '{';
  tabela[90] = '|';
  tabela[91] = '}';
}

void MatrizIdentidade (double **a, int n) {
  for (int i=0; i < n; i++) {
    for (int j=0; j < n; j++) {
      if (i == j) {
        a[i][j] = 1;
      }
      else {
        a[i][j] = 0;
      }
    }
  }
}

double **InverteMatriz (double **a, int tamanho) {
  double **b;
  b = malloc (tamanho * sizeof(double));
  for (int i=0; i < tamanho; i++) {
    b[i] = malloc(tamanho * sizeof(double));
  }
  MatrizIdentidade(b, tamanho);
  for (int i=0; i < tamanho; i++) {
    int cont = tamanho;
    while (a[i][i] == 0) { //É necessário trocar a linha
      cont--;
      for (int j=0; j < tamanho; j++) {
        double aux = a[i][j];
        a[i][j] = a[cont][j];
        a[cont][j] = aux;
        aux = b[i][j];
        b[i][j] = b[cont][j];
        b[cont][j] = aux;
      }
    }
    if (a[i][i] != 1) { //É necessário pivotar a linha
      double pivo = a[i][i];
      for (int j=0; j < tamanho; j++) {
        a[i][j] /= pivo; //Dividindo todos da linha pelo pivô
        b[i][j] /= pivo;
      }
    }
    //Linha pivotada!
    //Próximo passo: zerar a coluna do pivô
    for (int j = 0; j < tamanho; j++) {
      if (j != i) {
        double multiplicador = a[j][i];
        for (int k = 0; k < tamanho; k++) {
          a[j][k] -= (multiplicador*a[i][k]);
          b[j][k] -= (multiplicador*b[i][k]);
        }
      }
    }
  }
  return b;
}

double **MultiplicaMatrizes(double **a, double **b, int n) {
  double **x;
  x = malloc (n * sizeof(double));
  for (int i=0; i < n; i++) {
    x[i] = malloc(n * sizeof(double));
    for (int j=0; j < n; j++) {
      x[i][j] = 0;
      for (int k=0; k < n; k++) {
        x[i][j] += a[i][k]*b[k][j];
      }
    }
  }
  return x;
}

int main(int argc, char *argv[]) {
  char tabela[92], nome_arquivo[10], texto[100], aux[100], mensagem[100];
  int k, cont;
  double **a, **b, **x;
  FILE *arquivo;

  MontaTabela(tabela);

  scanf("%s", nome_arquivo);
  getchar();

  arquivo = fopen(nome_arquivo, "r");
  if (!arquivo) {
    printf("Arquivo não encontrado\n");
    return 1;
  }

  strcpy(aux, "");
  strcpy(texto, "");
  while (fgets(aux, sizeof aux, arquivo) != NULL) {
    strcat(texto, aux);
  }

  k = sqrt((strlen(texto)));

  a = malloc (k * sizeof(double));
  b = malloc (k * sizeof(double));
  x = malloc (k * sizeof(double));
  for (int i=0; i < k; i++) {
    a[i] = malloc(k * sizeof(double));
    b[i] = malloc(k * sizeof(double));
    x[i] = malloc(k * sizeof(double));
  }

  cont = 0;
  for (int i=0; i < k; i++) {
    for (int j=0; j < k; j++) {
      if (texto[cont] == '\n') {
        cont++;
      }
      char *aux = strchr(tabela, texto[cont]);
      a[j][i] = (int)(aux - tabela);
      cont++;
      scanf("%lf", &b[i][j]);
    }
  }

  b = InverteMatriz(b, k);

  x = MultiplicaMatrizes(b, a, k);

  cont = 0;
  for (int i=0; i < k; i++) {
    for (int j=0; j < k; j++) {
      if ((((int)x[j][i]) <= 91) && (((int)x[j][i]) >= 0)) {
        mensagem[cont] = tabela[(int)x[j][i]];
        cont++;
      }
    }
  }

  printf("%s\n", mensagem);

  return 0;
}
