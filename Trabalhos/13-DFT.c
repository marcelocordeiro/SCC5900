/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 30/05/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

typedef double complex cplx;

int partition(double *mags, int *index, cplx *vector, int left, int right) {
	int i, j;
  double aux1;
  int aux2;
  cplx aux3;
	i = left;
	for (j = i+1; j <= right; j++) {
		if (mags[j] > mags[left]) {
			++i;
      aux1 = mags[i];
      mags[i] = mags[j];
      mags[j] = aux1;
      aux2 = index[i];
      index[i] = index[j];
      index[j] = aux2;
      aux3 = vector[i];
      vector[i] = vector[j];
      vector[j] = aux3;
		}
	}
  aux1 = mags[i];
  mags[i] = mags[left];
  mags[left] = aux1;
  aux2 = index[i];
  index[i] = index[left];
  index[left] = aux2;
  aux3 = vector[i];
  vector[i] = vector[left];
  vector[left] = aux3;
	return i;
}


void quicksort_descending(double *mags, int *index, cplx *vector, int left, int right) {
	int r;
	if (left < right) {
		r = partition(mags, index, vector, left, right);
		quicksort_descending(mags, index, vector, left, r-1);
		quicksort_descending(mags, index, vector, r+1, right);
	}
}

void dft(cplx *vetor, int n, cplx *resultado) {
  double aux1;
  cplx aux2;
  for (int i=0; i < ((n/2) + 1); i++) {
    for (int j=0; j < n; j++) {
      aux1 = (double)((double)j/(double)n);
      aux2 = (cplx) (-1.0 * I * 2.0 * M_PI * (i * 1.0) * aux1);
      resultado[i] += (cplx) vetor[j] * cpow(M_E, aux2);
    }
    if (i == 0) {
      resultado[i] = (cplx) (resultado[i] * (double)((double)1/(double)n));
    }
    else {
      resultado[i] = (cplx) (resultado[i] * (double)((double)2/(double)n));
    }
  }
}

void dft_inverse(cplx *vetor, int n, cplx *resultado) {
  double aux1;
  cplx aux2;
  for (int i=0; i < n; i++) {
    for (int j=0; j < ((n/2) + 1); j++) {
      aux1 = (double)((double)j/(double)n);
      aux2 = (cplx) (I * 2.0 * M_PI * (i * 1.0) * aux1);
      resultado[i] += (cplx) vetor[j] * cpow(M_E, aux2);
    }
  }
}

double magnitude(double a, double b) {
  return sqrt(pow(a, 2) + pow(b, 2));
}

int main(int argc, char *argv[]) {
  FILE *audio;
  char nome_arquivo[20];
  unsigned char byte;
  int c, n, cont_mag, *index;
  double *mags;
  cplx *resultado, *inversa, *aux, *input = NULL;

  scanf("%s %d", nome_arquivo, &c);

  audio = fopen(nome_arquivo, "rb");
  if (!audio) {
    printf("File not found.\n");
    return 1;
  }

  n = 0;
  while (fread(&byte, sizeof(char), 1, audio) > 0) {
    n++;
    input = realloc(input, n * sizeof(cplx));
    input[n-1] = (double) byte;
  }

  resultado = calloc(((int)(n/2) + 1), sizeof(cplx));
  dft(input, n, resultado);

  mags = malloc(((int)(n/2) + 1) * sizeof(double));
  index = malloc(((int)(n/2) + 1) * sizeof(int));
  cont_mag = 0;
  for (int i=0; i < ((n/2) + 1); i++) {
    mags[i] = magnitude(creal(resultado[i]), cimag(resultado[i]));
    if (mags[i] > 0.1) {
      cont_mag++;
    }
    index[i] = i;
  }

  quicksort_descending(mags, index, resultado, 0, (int)((n/2)+1));

  for (int i=c; i < ((n/2) + 1); i++) {
    resultado[i] = 0;
  }

  aux = malloc(((int)(n/2) + 1) * sizeof(cplx));
  for (int i=0; i < ((n/2) + 1); i++) {
    aux[index[i]] = resultado[i];
  }
  for (int i=0; i < ((n/2) + 1); i++) {
    resultado[i] = aux[i];
  }

  inversa = calloc(n, sizeof(cplx));
  dft_inverse(resultado, n, inversa);

  printf("%d\n", n);
  printf("%d\n", cont_mag);
  for (int i=0; i < c; i++) {
    printf("%d ", (int) mags[i]);
  }
  printf("\n");
  for (int i=0; i < n; i++) {
    printf("%d\n", (unsigned char) round(creal(inversa[i])));
  }

  fclose(audio);
  free(index);
  free(mags);
  free(resultado);
  free(inversa);
  free(aux);
  free(input);

  return 0;
}
