/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega:
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
  FILE *audio;
  unsigned char aux;
  char nome_arquivo[20];

  scanf("%s", nome_arquivo);
  getchar();

  audio = fopen(nome_arquivo,"rb");
  if (!audio) {
    printf("Arquivo não encontrado\n");
    return 1;
  }

  while (!feof(audio)) {
    fread(&aux, 1, 1, audio);
    printf("%d\n", aux);
  }

  fclose(audio);

  return 0;
}
