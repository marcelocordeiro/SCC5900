/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <string.h>

#define MAX 999

typedef enum {
	FALSE,
	TRUE
} BOOL;

double minDist = DBL_MAX;
int *best;

BOOL is_vector(int *vector, int id, int element) {
	int j;

	for (j = 0; j < id; j++)
		if (vector[j] == element)
			return TRUE;
	return FALSE;
}

double cost(int *vector, int id, int n, double **distances) {

	if (id < 2) return 0;

	int i;
	double sum = 0.0;
	for (i = 0; i < id-1; i++)
		sum += distances[vector[i]][vector[i+1]];

	if (i == n-1) sum += distances[vector[n-1]][vector[0]];

	return sum;
}

void produce_solution(int *vector, int id, int n, double **distances) {
	int i;

	if (id < n) {

		for (i = 0; i < n; i++) {
			if (!is_vector(vector, id, i)) {
				vector[id] = i;
				produce_solution(vector, id+1, n, distances);
			}
		}

		double c = cost(vector, id+1, n, distances);
		if (c > minDist) return;

	} else {
		// Calcular o custo
		double c = cost(vector, n, n, distances);
		if (c < minDist) {
			minDist = c;
			memcpy(best, vector, sizeof(int) * n);
		}
	}
}

int main(int argc, char *argv[]) {
  double **distances, *x, *y;
  int k, *vector;

  scanf("%d", &k);

  x = malloc(k * sizeof(double));
  y = malloc(k * sizeof(double));

  for (int i = 0; i < k; i++) {
    scanf("%lf %lf", &x[i], &y[i]);
  }

  distances = malloc(k * sizeof(double*));
	for (int i = 0; i < k; i++) {
		distances[i] = calloc(k, sizeof(double));
	}

  for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			distances[i][j] = sqrt(pow((x[i] - x[j]), 2) + pow((y[i] - y[j]), 2));
		}
	}

  vector = malloc(k * sizeof(int));
	best = malloc(k * sizeof(int));
	produce_solution(vector, 0, k, distances);
  printf("%.6lf\n", minDist);

  return 0;
}
