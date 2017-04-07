/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 26/03/2017
*/

#include <stdio.h>
#include <stdlib.h>

void GaussJordan (int tamanho, double **a, double *b) {
  for (int i=0; i < tamanho; i++) {
    int cont = tamanho;
    while (a[i][i] == 0) { //É necessário trocar a linha
      cont--;
      for (int j=0; j < tamanho; j++) {
        double aux = a[i][j];
        a[i][j] = a[cont][j];
        a[cont][j] = aux;
      }
      double aux = b[i];
      b[i] = b[cont];
      b[cont] = aux;
    }
    if (a[i][i] != 1) { //É necessário pivotar a linha
      double pivo = a[i][i];
      for (int j=0; j < tamanho; j++) {
        a[i][j] /= pivo; //Dividindo todos da linha pelo pivô
      }
      b[i] /= pivo;
    }
    //Linha pivotada!
    //Próximo passo: zerar a coluna do pivô
    for (int j = 0; j < tamanho; j++) {
      if (j != i) {
        double multiplicador = a[j][i];
        for (int k = 0; k < tamanho; k++) {
          a[j][k] -= (multiplicador*a[i][k]);
        }
        b[j] -= (multiplicador*b[i]);
      }
    }
  }
}

int main(int argc, char *argv[]) {
  int tamanho;
  double **a, *b;
  scanf("%d", &tamanho);
  b = malloc (tamanho * sizeof(double));
  a = malloc (tamanho * sizeof(double));
  for (int i=0; i < tamanho; i++) {
    a[i] = malloc(tamanho * sizeof(double));
    for (int j=0; j < tamanho; j++) {
      scanf("%lf", &a[i][j]);
    }
  }
  for (int i=0; i < tamanho; i++) {
    scanf("%lf", &b[i]);
  }

  GaussJordan(tamanho, a, b);

  for (int i=0; i < tamanho; i++) {
    printf("%.6lf\n", b[i]);
  }

  free(a);
  free(b);
  b = NULL;
  for (int i=0; i < tamanho; i++)
    a[i] = NULL;
  return 0;
}
