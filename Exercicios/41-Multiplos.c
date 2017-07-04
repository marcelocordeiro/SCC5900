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

int searchVec(int *vector, int n, int num) {
  for (int i = 0; i < n; i++) {
    if (vector[i] == num) {
      return 1;
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  int n, i, j, aux1, aux2, *vector, count = 0;

  scanf("%d %d %d", &n, &i, &j);

  vector = malloc(n * 3 * sizeof(int));

  for (int k = 0; count < n * 3; k++) {
    aux1 = k * i;
    aux2 = k * j;
    if (aux1 == aux2) {
      if (!searchVec(vector, count, aux1)) {
        vector[count] = aux1;
        count++;
      }
    }
    else {
      if (count >= 1) {
        if (vector[count-1] == aux1) {
          if (!searchVec(vector, count, aux2)) {
            vector[count] = aux2;
            count++;
          }
        }
        else {
          if (vector[count-1] == aux2) {
            if (!searchVec(vector, count, aux1)) {
              vector[count] = aux1;
              count++;
            }
          }
          else {
            if (!searchVec(vector, count, aux1)) {
              vector[count] = aux1;
              count++;
            }
            if (!searchVec(vector, count, aux2)) {
              vector[count] = aux2;
              count++;
            }
          }
        }
      }
      else {
        if (!searchVec(vector, count, aux1)) {
          vector[count] = aux1;
          count++;
        }
        if (!searchVec(vector, count, aux2)) {
          vector[count] = aux2;
          count++;
        }
      }
    }
  }

  mergesort(vector, 0, (n * 3) - 1);

  for (int k = 0; k < n; k++) {
    printf("%d\n", vector[k]);
  }

  return 0;
}
