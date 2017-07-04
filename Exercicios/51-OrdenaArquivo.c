/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

struct person {
  char name[500], cpf[15];
  int age;
  double ncpf;
};

void merge(struct person **vector, int start, int middle, int end) {
	struct person **left, **right;
	int nleft, nright;
	int counter, l, r, i;

	nleft = middle - start + 2;
	nright = end - middle + 1;

	left = malloc(nleft * sizeof(struct person*));
	right = malloc(nright * sizeof(struct person*));

	counter = 0;
	for (i = start; i <= middle; i++) {
    left[counter] = malloc(sizeof(struct person));
    memcpy(left[counter], vector[i], sizeof(struct person));
    counter++;
  }
  left[counter] = calloc(1, sizeof(struct person));
	left[counter]->ncpf = DBL_MAX;

	counter = 0;
	for (i = middle+1; i <= end; i++) {
    right[counter] = malloc(sizeof(struct person));
    memcpy(right[counter], vector[i], sizeof(struct person));
    counter++;
  }
  right[counter] = calloc(1, sizeof(struct person));
	right[counter]->ncpf = DBL_MAX;

	// Intercalacao
	l = r = 0;
	for (i = start; i <= end; i++) {
		if (left[l]->ncpf <= right[r]->ncpf) {
      memcpy(vector[i], left[l], sizeof(struct person));
      l++;
		} else {
      memcpy(vector[i], right[r], sizeof(struct person));
      r++;
		}
	}
}

void mergesort(struct person **vector, int start, int end) {
	int middle;

	if (start < end) {
		middle = (end + start) / 2;
		mergesort(vector, start, middle);
		mergesort(vector, middle+1, end);
		merge(vector, start, middle, end);
	}
}

int main(int argc, char *argv[]) {
  FILE *file1, *file2;
  struct person **people = NULL;
  char nome1[50], nome2[50], name[500], cpf[15];
  int age, count = 0;

  scanf("%s", nome1);
  getchar();
  scanf("%s", nome2);
  getchar();

  file1 = fopen(nome1, "r");
  file2 = fopen(nome2, "r");

  while (fscanf(file1, "%s %[^\n]s %d", cpf, name, &age) > 0) {
    fscanf(file1, "%d", &age);
    // printf("cpf %s, name %s, age %d\n", cpf, name, age);
    people = realloc(people, (count + 1) * sizeof(struct person*));
    people[count] = malloc(sizeof(struct person));
    strcpy(people[count]->cpf, cpf);
    strcpy(people[count]->name, name);
    people[count]->age = age;
    people[count]->ncpf = ((cpf[0] - '0') * 100000000) + ((cpf[1] - '0') * 10000000) + ((cpf[2] - '0') * 1000000) + ((cpf[4] - '0') * 100000) + ((cpf[5] - '0') * 10000) + ((cpf[6] - '0') * 1000) + ((cpf[8] - '0') * 100) + ((cpf[9] - '0') * 10) + ((cpf[10] - '0'));
    count++;
  }

  while (fscanf(file2, "%s %[^\n]s %d", cpf, name, &age) > 0) {
    fscanf(file2, "%d", &age);
    // printf("cpf %s, name %s, age %d\n", cpf, name, age);
    people = realloc(people, (count + 1) * sizeof(struct person*));
    people[count] = malloc(sizeof(struct person));
    strcpy(people[count]->cpf, cpf);
    strcpy(people[count]->name, name);
    people[count]->age = age;
    people[count]->ncpf = ((cpf[0] - '0') * 100000000) + ((cpf[1] - '0') * 10000000) + ((cpf[2] - '0') * 1000000) + ((cpf[4] - '0') * 100000) + ((cpf[5] - '0') * 10000) + ((cpf[6] - '0') * 1000) + ((cpf[8] - '0') * 100) + ((cpf[9] - '0') * 10) + ((cpf[10] - '0'));
    count++;
  }

  mergesort(people, 0, count-1);

  for (int i = 0; i < count; i++) {
    printf("%s\n%s\n%d\n", people[i]->cpf, people[i]->name, people[i]->age);
  }

  return 0;
}
