#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
  int k;
  double **a, *b;
  scanf("%d", &k);
  b = malloc (k * sizeof(double));
  a = malloc (k * sizeof(double));
  for (int i=0; i < k; i++) {
    a[i] = malloc(k * sizeof(double));
    double aux;
    scanf("%lf", &aux); //Matriz
    scanf("%lf", &b[i]); //Resultado
    for (int j=0; j < k; j++) {
      a[i][j] = pow(aux, (k-j-1));
    }
  }

  GaussJordan(k, a, b);

  for (int i=0; i < k; i++) {
    printf("%.6lf\n", b[i]);
  }

  free(a);
  free(b);
  b = NULL;
  for (int i=0; i < k; i++)
    a[i] = NULL;
  return 0;
}
