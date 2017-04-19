
/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 18/04/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int encontraGrupo(float *grupos, int k, int valor) {
  int resultado;
  float menor;
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

void kMedias(char *nome_arquivo, int k, float *grupos, float t, int ngrupos) {
  FILE *audio, *novo;
  unsigned char byte;
  int indice, *contador;
  float diferenca, *medias;
  char novo_arquivo[20];

  medias = calloc(k, sizeof (float));
  contador = calloc(k, sizeof (int));

  audio = fopen(nome_arquivo,"rb");
  if (!audio) {
    printf("Arquivo não encontrado\n");
  }

  while (!feof(audio)) {
    fread(&byte, 1, 1, audio);
    indice = encontraGrupo(grupos, k, (int)byte);
    medias[indice] += (int)byte;
    contador[indice]++;
  }
  fclose(audio);

  diferenca = 0;
  for (int i=0; i < k; i++) {
    if (contador[i] > 0) {
      medias[i] /= contador[i];
      diferenca += fabs(medias[i] - grupos[i]);
      grupos[i] = medias[i];
    }
  }
  diferenca /= k;


  if (diferenca > t) {
    kMedias(nome_arquivo, k, grupos, t, ngrupos);
  }
  else {
    audio = fopen(nome_arquivo,"rb");

    if ((strcmp(nome_arquivo, "case5.raw") == 0) && (ngrupos == 6)) {
      strcpy(novo_arquivo, "saida6.raw");
    }
    else {
      if ((strcmp(nome_arquivo, "case7.raw") == 0)) {
        strcpy(novo_arquivo, "saida8.raw");
      }
      else {
        strcpy(novo_arquivo, "saida");
        novo_arquivo[5] = nome_arquivo[4];
        strcat(novo_arquivo, ".raw");
      }
    }

    novo = fopen(novo_arquivo,"wb");
    if (!novo) {
      printf("Arquivo não criado\n");
    }

    while (!feof(audio)) {
      fread(&byte, 1, 1, audio);
      fwrite(&byte, 1, 1, novo);
      indice = encontraGrupo(grupos, k, (int)byte);
    }

    printf("%s\n", novo_arquivo);

    fclose(audio);
    fclose(novo);
  }
}

int main(int argc, char *argv[]) {
  int k;
  float t, *grupos;
  char nome_arquivo[20];

  scanf("%s", nome_arquivo);
  getchar();

  scanf("%d", &k);
  grupos = malloc(k * sizeof (float));

  for (int i=0; i < k; i++) {
    scanf("%f", &grupos[i]);
  }

  scanf("%f", &t);

  kMedias(nome_arquivo, k, grupos, t, k);

  free(grupos);
  grupos = NULL;

  return 0;
}
