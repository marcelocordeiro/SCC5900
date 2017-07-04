/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void merge(int *vector, int start, int middle, int end) {
	int *left, *right;
	int nleft, nright;
	int counter, l, r, i;

	nleft = middle - start + 2;
	nright = end - middle + 1;

	left = (int *) malloc(sizeof(int) * nleft);
	right = (int *) malloc(sizeof(int) * nright);

	counter = 0;
	for (i = start; i <= middle; i++) left[counter++] = vector[i];
	left[counter] = INT_MAX;

	counter = 0;
	for (i = middle+1; i <= end; i++) right[counter++] = vector[i];
	right[counter] = INT_MAX;

	// Intercalacao
	l = r = 0;
	for (i = start; i <= end; i++) {
		if (left[l] <= right[r]) {
			vector[i] = left[l++];
		} else {
			vector[i] = right[r++];
		}
	}
}

void mergesort(int *vector, int start, int end) {
	int middle;

	if (start < end) {
		middle = (end + start) / 2;
		mergesort(vector, start, middle);
		mergesort(vector, middle+1, end);
		merge(vector, start, middle, end);
	}
}

int main(int argc, char *argv[]) {
  int n, *vector, k, count = 0;

  scanf("%d", &n);

  vector = malloc(n * sizeof(int));

  for (int i = 0; i < n; i++) {
    scanf("%d", &vector[i]);
  }

  scanf("%d", &k);

  mergesort(vector, 0, n-1);

  for (int i = 0; i < n; i++) {
    printf("%d\n", vector[i]);
  }

  for (int i = 0; i < n; i++) {
    if (vector[i] == k) {
      printf("%d ", i);
      while (vector[i] == k) {
        i++;
        count++;
      }
      printf("%d\n%d", i-1, count);
    }
  }

  return 0;
}
