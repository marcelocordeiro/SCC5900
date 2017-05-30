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

void show_cplx(cplx *vetor, int n) {
  for (int i=0; i < n; i++) {
    if (!cimag(vetor[i]))
      printf("(%.2lf)", creal(vetor[i]));
    else
      printf("(%.2lf %.2lf)", creal(vetor[i]), cimag(vetor[i]));
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

void inverteVetor(double **mags, int **index, cplx **vector, int n) {
  double *aux1;
  int *aux2;
  cplx *aux3;
  aux1 = malloc(n * sizeof(double));
  aux2 = malloc(n * sizeof(int));
  aux3 = malloc(n * sizeof(cplx));

  for (int i=0; i < n; i++) {
    aux1[n-i-1] = (*mags)[i];
    aux2[n-i-1] = (*index)[i];
    aux3[n-i-1] = (*vector)[i];
  }

  *mags = aux1;
  *index = aux2;
  *vector = aux3;
}

void dft(cplx *input, int n, cplx *resultado) {
  for (int i=0; i < n; i++) {
    for (int j=0; j < n; j++) {
      // printf("resultado[%d] += %g * (cos(-1 * ((2 * %g * %d * %d) / %d)) + I * sin(-1 * ((2 * %g * %d * %d) / %d)))\n", i, creal(input[j]), M_PI, i, j, n, M_PI, i, j, n);
      // printf("resultado[%d] += (%g + %g)\n", i, creal(input[j] * (cos(-1 * ((2 * M_PI * i * j) / n)) + I * sin(-1 * ((2 * M_PI * i * j) / n)))), cimag(input[j] * (cos(-1 * ((2 * M_PI * i * j) / n)) + I * sin(-1 * ((2 * M_PI * i * j) / n)))));
      resultado[i] += input[j] * (cos(-1 * ((2 * M_PI * i * j) / n)) + I * sin(-1 * ((2 * M_PI * i * j) / n)));
      // printf("resultado[%d] = (%g + %g)\n\n", i, creal(resultado[j]), cimag(resultado[j]));
    }
  }
}

void dft_inverse(cplx *input, int n, cplx *resultado) {
  for (int i=0; i < n; i++) {
    for (int j=0; j < n; j++) {
      // printf("resultado[%d] += %g * (cos(-1 * ((2 * %g * %d * %d) / %d)) + I * sin(-1 * ((2 * %g * %d * %d) / %d)))\n", i, creal(input[j]), M_PI, i, j, n, M_PI, i, j, n);
      // printf("resultado[%d] += (%g + %g)\n", i, creal(input[j] * (cos(-1 * ((2 * M_PI * i * j) / n)) + I * sin(-1 * ((2 * M_PI * i * j) / n)))), cimag(input[j] * (cos(-1 * ((2 * M_PI * i * j) / n)) + I * sin(-1 * ((2 * M_PI * i * j) / n)))));
      resultado[i] += input[j] * (cos((2 * M_PI * i * j) / n) + I * sin((2 * M_PI * i * j) / n));
      // printf("resultado[%d] = (%g + %g)\n\n", i, creal(resultado[j]), cimag(resultado[j]));
    }
    // resultado[i] /= (double) n;
  }
}

double magnitude(double a, double b) {
  return sqrt(pow(a, 2) + pow(b, 2));
}

int main(int argc, char *argv[]) {
  FILE *audio;
  char nome_arquivo[20];
  unsigned char byte;
  int c, n, *index;
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
  resultado = calloc(n, sizeof(cplx));
  dft(input, n, resultado);
  // printf("Chamei DFT\n\n");

  printf("%d\n", n);
  show_cplx(input, n);
  show_cplx(resultado, n);

  mags = malloc(n * sizeof(double));
  index = malloc(n * sizeof(int));
  for (int i=0; i < n; i++) {
    mags[i] = magnitude(creal(resultado[i]), cimag(resultado[i]));
    index[i] = i;
  }

  // show_double(mags, n);
  // show_int(index, n);
  // show_cplx(resultado, n);
  // printf("Quick\n");
  quicksort(mags, index, resultado, 0, n);
  // show_double(mags, n);
  // show_int(index, n);
  // show_cplx(resultado, n);
  // printf("Inverte vetor\n");
  inverteVetor(&mags, &index, &resultado, n);
  // show_double(mags, n);
  // show_int(index, n);
  // show_cplx(resultado, n);

  for (int i=c; i < n; i++) {
    resultado[i] = 0;
  }
  // printf("Zerei\n");
  // show_cplx(resultado, n);

  aux = calloc(n, sizeof(cplx));
  for (int i=0; i < n; i++) {
    aux[index[i]] = resultado[i];
  }
  resultado = aux;
  // printf("Voltei\n");
  // show_cplx(resultado, n);

  // printf("Vou chamar a inversa\n");
  inversa = calloc(n, sizeof(cplx));
  dft_inverse(resultado, n, inversa);
  // printf("Inverti\n");
  // show_cplx(inversa, n);

  return 0;
}
