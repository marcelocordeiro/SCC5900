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

int main(int argc, char *argv[]) {
  FILE *audio;
  int byte, k, t, indice, diferenca, nova_media, *grupos, *medias, *contador;
  char nome_arquivo[20];

  scanf("%s", nome_arquivo);
  getchar();

  scanf("%d", &k);
  grupos = malloc(k * sizeof (int));
  medias = calloc(k, sizeof (int));
  contador = calloc(k, sizeof (int));

  for (int i=0; i < k; i++) {
    scanf("%d", &grupos[i]);
  }

  scanf("%d", &t);

  audio = fopen(nome_arquivo,"rb");
  if (!audio) {
    printf("Arquivo não encontrado\n");
    return 1;
  }

  while (!feof(audio)) {
    fread(&byte, 1, 1, audio);
    indice = encontraGrupo(grupos, k, byte);
    medias[indice] += byte;
    contador[indice]++;
  }

  diferenca = 0;
  for (int i=0; i < k; i++) {
    nova_media = (int) floor(medias[i] / contador[i]);
    diferenca += abs(nova_media - medias[i]);
  }
  diferenca /= k;

  fclose(audio);
  free(grupos);
  free(medias);
  free(contador);
  grupos = NULL;
  medias = NULL;
  contador = NULL;

  return 0;
}
