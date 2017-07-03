/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 03/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

struct pais {
  int medalhas[3];
  char desc[3];
};

void merge(struct pais **vector, int type, int start, int middle, int end) {
	struct pais **left, **right;
	int nleft, nright;
	int counter, l, r, i;

	nleft = middle - start + 2;
	nright = end - middle + 1;

	left = malloc(sizeof(struct pais*) * nleft);
	right = malloc(sizeof(struct pais*) * nright);

	counter = 0;
	for (i = start; i <= middle; i++) {
		left[counter] = malloc(sizeof(struct pais));
		memcpy(left[counter], vector[i], sizeof(struct pais));
		counter++;
	}
	left[counter] = calloc(1, sizeof(struct pais));
	left[counter]->medalhas[type] = -1;

	counter = 0;
	for (i = middle+1; i <= end; i++) {
		right[counter] = malloc(sizeof(struct pais));
		memcpy(right[counter], vector[i], sizeof(struct pais));
		counter++;
	}
	right[counter] = calloc(1, sizeof(struct pais));
	right[counter]->medalhas[type] = -1;

	// Intercalacao
	l = r = 0;
	for (i = start; i <= end; i++) {
		if (left[l]->medalhas[type] >= right[r]->medalhas[type]) {
			memcpy(vector[i], left[l], sizeof(struct pais));
			l++;
		} else {
			memcpy(vector[i], right[r], sizeof(struct pais));
			r++;
		}
	}
}

void mergesort(struct pais **vector, int type, int start, int end) {
	int middle;

	if (start < end) {
		middle = (end + start) / 2;
		mergesort(vector, type, start, middle);
		mergesort(vector, type, middle+1, end);
		merge(vector, type, start, middle, end);
	}
}

void printMedalhas(struct pais **paises, int n) {
	for (int i = 0; i < n; i++) {
		printf("%s %d %d %d\n", paises[i]->desc, paises[i]->medalhas[0], paises[i]->medalhas[1], paises[i]->medalhas[2]);
	}
}

int main(int argc, char *argv[]) {
  int n;
  struct pais **paises;

  scanf("%d", &n);

  paises = malloc(n * sizeof(struct pais*));

  for (int i = 0; i < n; i++) {
		paises[i] = malloc(n * sizeof(struct pais));
		scanf("%s %d %d %d", paises[i]->desc, &paises[i]->medalhas[0], &paises[i]->medalhas[1], &paises[i]->medalhas[2]);
  }

	mergesort(paises, 2, 0, n-1);
	mergesort(paises, 1, 0, n-1);
	mergesort(paises, 0, 0, n-1);

	printMedalhas(paises, n);

  return 0;
}
