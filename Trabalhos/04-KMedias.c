/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega:
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
  FILE *audio;
  int byte, k, t, *grupos;
  char nome_arquivo[20];

  scanf("%s", nome_arquivo);
  getchar();

  scanf("%d", &k);
  grupos = malloc(k * sizeof (int));

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
    
  }

  fclose(audio);

  return 0;
}
