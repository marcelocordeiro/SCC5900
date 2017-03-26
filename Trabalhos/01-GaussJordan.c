#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int size_a;
  double **a, *b, *x;
  scanf("%d", &size_a);
  b = malloc (size_a * sizeof(double));
  x = malloc (size_a * sizeof(double));
  a = malloc (size_a * sizeof(double));
  for (int i=0; i < size_a; i++) {
    a[i] = malloc(size_a * sizeof(double));
    for (int j=0; j < size_a; j++) {
      scanf("%lf", &a[i][j]);
    }
  }
  for (int i=0; i < size_a; i++) {
    scanf("%lf", &b[i]);
  }

  free(a);
  free(b);
  free(x);
  b = x = NULL;
  for (int i=0; i < size_a; i++)
    a[i] = NULL;
  return 0;
}
