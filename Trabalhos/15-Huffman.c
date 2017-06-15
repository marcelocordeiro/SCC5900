#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char nome_arquivo[20], *extensao;

    scanf("%s", nome_arquivo);

    extensao = strstr(nome_arquivo, ".");

    // printf("Nome do arquivo: %s\nExtensão: %s\n", nome_arquivo, extensao);

    switch (extensao[1]) {
      case 't': //Compactar
        // printf("Compactar %s\n", nome_arquivo);

        break;
      case 'h': //Descompactar
        
        // printf("Descompactar %s\n", nome_arquivo);
        break;
    }

    return 0;
}
