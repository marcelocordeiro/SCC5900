#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *texto, *binario;
  int byte;
  int n;

  texto = fopen("audio5.txt", "r");
  if (!texto) {
    printf("File not found.\n");
    return 1;
  }

  binario = fopen("audio5.raw", "wb");

  n = 0;
  while (fscanf(texto, "%d", &byte) > 0) {
    fwrite(&byte, sizeof(char), 1, binario);
    n++;
    printf("%d ", (int) byte);
  }

  printf("\n\n%d\n", n);

  fclose(texto);
  fclose(binario);

  return 0;
}
