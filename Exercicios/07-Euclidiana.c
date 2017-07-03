/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 03/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int n;
    float *x, *y, dist = 0;

    scanf("%d", &n);

    x = malloc(n * sizeof(float));
    y = malloc(n * sizeof(float));

    for (int i = 0; i < n; i++) {
      scanf("%f %f\n", &x[i], &y[i]);
    }

    for (int i = 1; i < n; i++) {
      dist += sqrt(pow((x[i-1] - x[i]),2) + pow((y[i-1] - y[i]),2));
    }

    printf("%.4f", dist);

    return 0;
}
