
/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega:
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int partition(double *vector, int left, int right) {
	int i, j;
  double aux;
	i = left;
	for (j = i+1; j <= right; j++) {
		if (vector[j] < vector[left]) {
			++i;
      aux = vector[i];
      vector[i] = vector[j];
      vector[j] = aux;
		}
	}
  aux = vector[i];
  vector[i] = vector[left];
  vector[left] = aux;
	return i;
}


void quicksort(double *vector, int left, int right) {
	int r;
	if (left < right) {
		r = partition(vector, left, right);
		quicksort(vector, left, r-1);
		quicksort(vector, r+1, right);
	}
}

double *TransfDiscretaCosseno(double *vetor, int n) {
  double *vetor_transf;
  vetor_transf = calloc(n, sizeof(double));

  for (int k=0; k < n; k++) {
    for (int j=0; j < n; j++) {
      vetor_transf[k] += vetor[j] * cos((M_PI/n) * (j + 0.5) * k);
    }
  }

  return vetor_transf;
}

int main(int argc, char *argv[]) {
  FILE *audio;
  unsigned char byte;
  double *vetor, *vetor_transf;
  int k, n;
  char nome_arquivo[20];

  scanf("%s", nome_arquivo);
  getchar();

  scanf("%d", &k);

  audio = fopen(nome_arquivo,"rb");
  if (!audio) {
    printf("Arquivo não encontrado\n");
    return 1;
  }

  vetor = malloc(sizeof(double));
  n = 0;
  while (!feof(audio)) {
    fread(&byte, 1, 1, audio);
    vetor[n] = (double) byte;
    n++;
    vetor = realloc(vetor,(n+1) * sizeof(double));
  }

  vetor_transf = malloc(n * sizeof(double));

  vetor_transf = TransfDiscretaCosseno(vetor, n);

  fclose(audio);

  return 0;
}
