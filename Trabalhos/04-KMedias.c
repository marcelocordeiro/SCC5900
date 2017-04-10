
/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega:
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int encontraGrupo(double *grupos, int k, int valor) {
  int resultado;
  double menor;
  menor = fabs(valor - grupos[0]);
  resultado = 0;
  for (int i=1; i < k; i++) {
    if (fabs(valor - grupos[i]) < menor) {
      menor = fabs(valor - grupos[i]);
      resultado = i;
    }
  }
  return resultado;
}

void kMedias(char *nome_arquivo, int k, double *grupos, double t) {
  FILE *audio;//, *perai;
  unsigned char byte;//, help;
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
    // printf("(%d ", byte);
    indice = encontraGrupo(grupos, k, (int)byte);
    // printf("- Grupo %d - %.5f) ", (indice+1), grupos[indice]);
    medias[indice] += (int)byte;
    contador[indice]++;
  }
  fclose(audio);

  // printf("\nNovos grupos!\n");
  diferenca = 0;
  for (int i=0; i < k; i++) {
    if (contador[i] > 0) {
      medias[i] /= contador[i];
      diferenca += fabs(medias[i] - grupos[i]);
      grupos[i] = medias[i];
      // printf("\nGrupo %d: %.5f (%.5f / %d)\n", i+1, grupos[i], medias[i]*contador[i], contador[i]);
    }
  }
  diferenca /= k;

  // printf("\nDiferença: %.5f (%.5f / %d)\nT: %.5f\n\n", diferenca, diferenca*k, k, t);

  if (diferenca > t) {
    // printf("Vou chamar de novo\n");
    kMedias(nome_arquivo, k, grupos, t);
  }
  else {
    // printf("Terminou!\n");
    audio = fopen(nome_arquivo,"rb");
    // perai = fopen("saida1.raw","rb");

    while (!feof(audio)) {
      fread(&byte, 1, 1, audio);
      // fread(&help, 1, 1, perai);
      indice = encontraGrupo(grupos, k, (int)byte);
      fputc(floor(grupos[indice]), stdout);
      // printf("(%.0f %d)", floor(grupos[indice]), help);
    }
    fclose(audio);
  }
}

int main(int argc, char *argv[]) {
  int k;
  double t, *grupos;
  char nome_arquivo[20];

  scanf("%s", nome_arquivo);
  getchar();

  scanf("%d", &k);
  grupos = malloc(k * sizeof (double));

  for (int i=0; i < k; i++) {
    scanf("%lf", &grupos[i]);
  }

  scanf("%lf", &t);

  // printf("Vou chamar!\n");
  kMedias(nome_arquivo, k, grupos, t);
  // printf("\nChamei!\n");

  free(grupos);
  grupos = NULL;

  return 0;
}
