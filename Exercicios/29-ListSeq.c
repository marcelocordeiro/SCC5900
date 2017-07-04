/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

struct list {
  double num;
  int freq;
};

void merge(struct list **vector, int start, int middle, int end) {
	struct list **left, **right;
	int nleft, nright;
	int counter, l, r, i;

	nleft = middle - start + 2;
	nright = end - middle + 1;

	left = malloc(sizeof(struct lis*) * nleft);
	right = malloc(sizeof(struct list*) * nright);

	counter = 0;
	for (i = start; i <= middle; i++) {
		left[counter] = malloc(sizeof(struct list));
		memcpy(left[counter], vector[i], sizeof(struct list));
		counter++;
	}
	left[counter] = calloc(1, sizeof(struct list));
	left[counter]->num = DBL_MAX;

	counter = 0;
	for (i = middle+1; i <= end; i++) {
		right[counter] = malloc(sizeof(struct list));
		memcpy(right[counter], vector[i], sizeof(struct list));
		counter++;
	}
	right[counter] = calloc(1, sizeof(struct list));
	right[counter]->num = DBL_MAX;

	// Intercalacao
	l = r = 0;
	for (i = start; i <= end; i++) {
		if (left[l]->num <= right[r]->num) {
			memcpy(vector[i], left[l], sizeof(struct list));
			l++;
		} else {
			memcpy(vector[i], right[r], sizeof(struct list));
			r++;
		}
	}
}

void mergesort(struct list **vector, int start, int end) {
	int middle;

	if (start < end) {
		middle = (end + start) / 2;
		mergesort(vector, start, middle);
		mergesort(vector, middle+1, end);
		merge(vector, start, middle, end);
	}
}

int main(int argc, char *argv[]) {
  int n, flag, count = 0;
  double aux;
  struct list **myList;

  scanf("%d", &n);

  myList = malloc(n * sizeof(struct list*));

  for (int i = 0; i < n; i++) {
    scanf("%lf", &aux);
    flag = 0;
    for (int j = 0; j < count; j++) {
      if (aux == myList[j]->num) {
        myList[j]->freq++;
        flag = 1;
        break;
      }
    }
    if (!flag) {
      myList[count] = calloc(1, sizeof(struct list));
      myList[count]->num = aux;
      count++;
    }
  }

	mergesort(myList, 0, count-1);

  for (int i = 0; i < count; i++) {
    printf("%.1lf %d\n", myList[i]->num, myList[i]->freq + 1);
  }

  return 0;
}
