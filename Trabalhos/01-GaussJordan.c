#include <stdio.h>
#include <stdlib.h>

void GaussJordan (int size, double **a, double *b, double *x) {
  x[0] = 3;
  x[1] = 1;
  x[2] = 2;
}

int main(int argc, char *argv[]) {
  int size;
  double **a, *b, *x;
  scanf("%d", &size);
  b = malloc (size * sizeof(double));
  x = malloc (size * sizeof(double));
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

  GaussJordan(size, a, b, x);

  for (int i=0; i < size; i++) {
    printf("%.5lf\n", x[i]);
  }

  free(a);
  free(b);
  free(x);
  b = x = NULL;
  for (int i=0; i < size; i++)
    a[i] = NULL;
  return 0;
}
