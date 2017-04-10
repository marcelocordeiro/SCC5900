/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega:
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int encontraGrupo(int *grupos, int k, int valor) {
  int menor, resultado;
  menor = abs(valor - grupos[0]);
  resultado = 0;
  for (int i=1; i < k; i++) {
    if (abs(valor - grupos[i]) < menor) {
      menor = abs(valor - grupos[i]);
      resultado = i;
    }
  }
  return resultado;
}

void kMedias(char *nome_arquivo, int k, int *grupos, double t) {
  FILE *audio, *perai;
  unsigned char byte, help;
  int indice, *contador;
  double diferenca, *medias;

  medias = calloc(k, sizeof (double));
  contador = calloc(k, sizeof (int));

  audio = fopen(nome_arquivo,"rb");
  if (!audio) {
    printf("Arquivo não encontrado\n");
  }

  // printf("Bora ler o arquivo?\n");
  while (!feof(audio)) {
    fread(&byte, 1, 1, audio);
    // printf("%d ", byte);
    indice = encontraGrupo(grupos, k, (int)byte);
    // printf("- Grupo %d (%d)--- ", (indice+1), grupos[indice]);
    medias[indice] += (int)byte;
    contador[indice]++;
  }
  fclose(audio);

  // printf("\nNovos grupos!\n");
  diferenca = 0;
  for (int i=0; i < k; i++) {
    if (contador[i] > 0) {
      medias[i] = medias[i] / contador[i];
      diferenca += fabs(grupos[i] - medias[i]);
      grupos[i] = floor(medias[i]);
      // printf("Grupo %d: %d\n", i+1, grupos[i]);
    }
  }
  diferenca /= k;

  printf("\nDiferença: %.5f\nT: %.5f\n", diferenca, t);

  if (diferenca > t) {
    // printf("Vou chamar de novo\n");
    kMedias(nome_arquivo, k, grupos, t);
  }
  else {
    // printf("Terminou!\n");
    audio = fopen(nome_arquivo,"rb");
    perai = fopen("saida1.raw","rb");

    while (!feof(audio)) {
      fread(&byte, 1, 1, audio);
      fread(&help, 1, 1, perai);
      indice = encontraGrupo(grupos, k, (int)byte);
      // fputc(grupos[indice], stdout);
      printf("(%d %d)", grupos[indice], help);
    }
    fclose(audio);
  }
}

int main(int argc, char *argv[]) {
  int k, *grupos;
  double t;
  char nome_arquivo[20];

  scanf("%s", nome_arquivo);
  getchar();

  scanf("%d", &k);
  grupos = malloc(k * sizeof (int));

  for (int i=0; i < k; i++) {
    scanf("%d", &grupos[i]);
  }

  scanf("%lf", &t);

  printf("Vou chamar!\n");
  kMedias(nome_arquivo, k, grupos, t);
  printf("\nChamei!\n");

  free(grupos);
  grupos = NULL;

  return 0;
}
