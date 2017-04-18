
/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega:
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *audio;
  unsigned char byte;
  double *vetor;
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

  fclose(audio);

  return 0;
}
