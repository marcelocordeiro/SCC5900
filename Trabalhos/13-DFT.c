/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 29/05/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

typedef double complex cplx;

#define PI 3.14159265358979323846
#define e 2.71828182845904523536

void show_cplx(cplx *vetor, int n) {
  for (int i=0; i < n; i++) {
    if (!cimag(vetor[i]))
      printf("(%lf)", creal(vetor[i]));
    else
      printf("(%lf %lfi)", creal(vetor[i]), cimag(vetor[i]));
  }
  printf("\n\n");
}

void show_int(int *vetor, int n) {
  for (int i=0; i < n; i++) {
    printf("%d ", vetor[i]);
  }
  printf("\n\n");
}

void show_double(double *vetor, int n) {
  for (int i=0; i < n; i++) {
    printf("%.2lf ", vetor[i]);
  }
  printf("\n\n");
}

int partition(double *mags, int *index, cplx *vector, int left, int right) {
	int i, j;
  double aux1;
  int aux2;
  cplx aux3;
	i = left;
	for (j = i+1; j <= right; j++) {
		if (mags[j] < mags[left]) {
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


void quicksort(double *mags, int *index, cplx *vector, int left, int right) {
	int r;
	if (left < right) {
		r = partition(mags, index, vector, left, right);
		quicksort(mags, index, vector, left, r-1);
		quicksort(mags, index, vector, r+1, right);
	}
}

void inverteVetor(double *mags, int *index, cplx *vector, int n) {
  double *aux1;
  int *aux2;
  cplx *aux3;
  aux1 = malloc(n * sizeof(double));
  aux2 = malloc(n * sizeof(int));
  aux3 = malloc(n * sizeof(cplx));

  for (int i=0; i < n; i++) {
    aux1[n-i-1] = mags[i];
    aux2[n-i-1] = index[i];
    aux3[n-i-1] = vector[i];
  }

  for (int i=0; i < n; i++) {
    mags[i] = aux1[i];
    index[i] = aux2[i];
    vector[i] = aux3[i];
  }
}

void dft(cplx *vetor, int n, cplx *resultado) {
  double aux1;
  cplx aux2;
  for (int i=2; i < ((n/2) + 1); i++) {
    for (int j=0; j < n; j++) {
      aux1 = (double)((double)j/(double)n);
      aux2 = (cplx) (-1.0 * I * 2.0 * PI * (i * 1.0) * aux1);
      resultado[i] += (cplx) vetor[j] * cpow(e, aux2);
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
  for (int i=2; i < n; i++) {
    for (int j=0; j < ((n/2) + 1); j++) {
      aux1 = (double)((double)j/(double)n);
      aux2 = (cplx) (I * 2.0 * PI * (i * 1.0) * aux1);
      resultado[i] += (cplx) vetor[j] * cpow(e, aux2);
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

  // cplx buf[] = {1, 1, 1, 1, 0, 0, 0, 0};
  // cplx buf2[] = {0, 0, 0, 0, 0, 0, 0, 0};
  // cplx buf3[] = {0, 0, 0, 0, 0, 0, 0, 0};
  // n = 8;
  //
  // show_cplx(buf, n);
  // show_cplx(buf2, n);
  // printf("Vou chamar DFT\n");
  // dft(buf, n, buf2);
  // printf("Chamei DFT\n\n");
  // show_cplx(buf, n);
  // show_cplx(buf2, n);
  // printf("Vou chamar a inversa\n");
  // dft_inverse(buf2, n, buf3);
  // printf("Chamei a inversa\n\n");
  // show_cplx(buf2, n);
  // show_cplx(buf3, n);

  // printf("Vou chamar DFT\n");
  resultado = calloc(((int)(n/2) + 1), sizeof(cplx));
  dft(input, n, resultado);
  // printf("Chamei DFT\n\n");
  //
  // printf("%d\n", n);
  // show_cplx(input, n);
  // show_cplx(resultado, n);

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

  // show_double(mags, n);
  // show_int(index, n);
  // show_cplx(resultado, n);
  // printf("Quick\n");
  quicksort(mags, index, resultado, 0, (int)((n/2)+1));
  // show_double(mags, n);
  // show_int(index, n);
  // show_cplx(resultado, n);
  // printf("Inverte vetor\n");
  inverteVetor(mags, index, resultado, (int)((n/2)+1));
  // show_double(mags, (int)((n/2)+1));
  // show_int(index, (int)((n/2)+1));
  // show_cplx(resultado, (int)((n/2)+1));

  for (int i=c; i < ((n/2) + 1); i++) {
    resultado[i] = 0;
  }
  // printf("Zerei\n");
  // show_cplx(resultado, n);

  aux = malloc(((int)(n/2) + 1) * sizeof(cplx));
  // for (int i=0; i < ((n/2) + 1); i++) {
  //   aux[index[i]] = resultado[i];
  // }
  // resultado = aux;
  // // printf("Voltei\n");
  // // show_cplx(resultado, n);
  //
  // // printf("Vou chamar a inversa\n");
  // inversa = calloc(n, sizeof(cplx));
  // dft_inverse(resultado, n, inversa);
  // // printf("Inverti\n");
  // // show_cplx(inversa, n);
  //
  // printf("%d\n", n);
  // printf("%d\n", cont_mag);
  // for (int i=0; i < c; i++) {
  //   printf("%d ", (int) mags[i]);
  // }
  // printf("\n");
  // for (int i=0; i < n; i++) {
  //   // printf("%d\n", (unsigned char) round(creal(inversa[i])));
  // }

  // fclose(audio);
  // free(index);
  // free(mags);
  // free(resultado);
  // free(inversa);
  // free(aux);
  // free(input);

  return 0;
}
