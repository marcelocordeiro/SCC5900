#include <stdio.h>
#include <stdlib.h>

void GaussJordan (int size, double **a, double *b) {
  for (int i=0; i < size; i++) {
    int cont = size;
    while (a[i][i] == 0) { //É necessário trocar a linha
      cont--;
      for (int j=0; j < size; j++) {
        double aux = a[i][j];
        a[i][j] = a[cont][j];
        a[cont][j] = aux;
        aux = b[i];
        b[i] = b[cont];
        b[cont] = aux;
      }
    }
    if (a[i][i] != 1) { //É necessário pivotar a linha
      double pivo = a[i][i];
      for (int j=0; j < size; j++) {
        a[i][j] /= pivo; //Dividindo todos da linha pelo pivô
      }
      b[i] /= pivo;
    }
    //Linha pivotada!
    //Próximo passo: zerar a coluna do pivô
    for (int j = 0; j < size; j++) {
      if (j != i) {
        double multiplicador = a[j][i];
        for (int k = 0; k < size; k++) {
          a[j][k] -= (multiplicador*a[i][k]);
        }
        b[j] -= (multiplicador*b[i]);
      }
    }
  }
}

int main(int argc, char *argv[]) {
  int size;
  double **a, *b;
  scanf("%d", &size);
  b = malloc (size * sizeof(double));
  a = malloc (size * sizeof(double));
  for (int i=0; i < size; i++) {
    a[i] = malloc(size * sizeof(double));
    for (int j=0; j < size; j++) {
      scanf("%lf", &a[i][j]);
    }
  }
  for (int i=0; i < size; i++) {
    scanf("%lf", &b[i]);
  }

  GaussJordan(size, a, b);

  for (int i=0; i < size; i++) {
    printf("%.6lf\n", b[i]);
  }

  free(a);
  free(b);
  b = NULL;
  for (int i=0; i < size; i++)
    a[i] = NULL;
  return 0;
}
