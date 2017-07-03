/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 26/04/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void merge(int *vector, int *extra1, int *extra2, char **extra3, int start, int middle, int end) {
	int *left, *right, *left2, *right2, *left3, *right3;
  char **left4, **right4;
	int nleft, nright;
	int counter, l, r, i;

	nleft = middle - start + 2;
	nright = end - middle + 1;

	left = malloc(sizeof(int) * nleft);
	right = malloc(sizeof(int) * nright);
	left2 = malloc(sizeof(int) * nleft);
	right2 = malloc(sizeof(int) * nright);
	left3 = malloc(sizeof(int) * nleft);
	right3 = malloc(sizeof(int) * nright);
	left4 = malloc(sizeof(char*) * nleft);
	right4 = malloc(sizeof(char*) * nright);

	counter = 0;
	for (i = start; i <= middle; i++) {
    left[counter] = vector[i];
    left2[counter] = extra1[i];
    left3[counter] = extra2[i];
    left4[counter] = malloc(3 * sizeof(char));
    left4[counter] = extra3[i];
    counter++;
  }
  left[counter] = INT_MAX;

	counter = 0;
	for (i = middle+1; i <= end; i++) {
    right[counter] = vector[i];
    right2[counter] = extra1[i];
    right3[counter] = extra2[i];
    right4[counter] = malloc(3 * sizeof(char));
    right4[counter] = extra3[i];
    counter++;
  }
  right[counter] = INT_MAX;

	// Intercalacao
	l = r = 0;
	for (i = start; i <= end; i++) {
		if (left[l] <= right[r]) {
			vector[i] = left[l];
			extra1[i] = left2[l];
			extra2[i] = left3[l];
      extra3[i] = left4[l];
      l++;
		} else {
			vector[i] = right[r];
			extra1[i] = right2[r];
			extra2[i] = right3[r];
      extra3[i] = right4[r];
      r++;
		}
	}
}

void mergesort(int *vector, int *extra1, int *extra2, char **extra3, int start, int end) {
	int middle;

	if (start < end) {
		middle = (end + start) / 2;
		mergesort(vector, extra1, extra2, extra3, start, middle);
		mergesort(vector, extra1, extra2, extra3, middle+1, end);
		merge(vector, extra1, extra2, extra3, start, middle, end);
	}
}


void ImprimeMedalhas(int *ouro, int *prata, int *bronze, char **desc, int n) {

  // for (int i = 0; i < n; i++) {
  //   printf("%s %d %d %d\n", desc[i], ouro[i], prata[i], bronze[i]);
  // }

  // printf("Hi\n");

  mergesort(bronze, ouro, prata, desc, 0, n);
  mergesort(prata, ouro, bronze, desc, 0, n);
  mergesort(ouro, prata, bronze, desc, 0, n);

  for (int i = 0; i < n; i++) {
    printf("%s %d %d %d\n", desc[i], ouro[i], prata[i], bronze[i]);
  }
}

int main(int argc, char *argv[]) {
  int n, *ouro, *prata, *bronze;
  char **desc;

  scanf("%d", &n);
  getchar();

  ouro = malloc(n * sizeof(int));
  prata = malloc(n * sizeof(int));
  bronze = malloc(n * sizeof(int));
  desc = malloc(n * sizeof(char*));

  for (int k = 0; k < n; k++) {
    desc[k] = malloc(3 * sizeof(char));
    scanf("%s", desc[k]);
    getchar();
    scanf("%d", &ouro[k]);
    scanf("%d", &prata[k]);
    scanf("%d", &bronze[k]);
  }

  ImprimeMedalhas(ouro, prata, bronze, desc, n);

  return 0;
}
