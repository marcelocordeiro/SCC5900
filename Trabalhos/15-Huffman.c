#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char nome_arquivo[20], extensao[20];

    scanf("%s", nome_arquivo);

    strcpy(extensao, nome_arquivo);
    strsep(&extensao, ".");

    printf("Nome do arquivo: %s\nExtensão: %s\n", nome_arquivo, extensao);

    return 0;
}