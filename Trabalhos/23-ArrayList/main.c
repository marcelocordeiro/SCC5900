/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 02/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <item.h>
#include <ArrayList.h>

int main(int argc, char *argv[]) {
  ArrayList *arrayList, *subArray;
  char comando[10];
  int chave, valor, pos1, pos2;

  arrayList = new_arrayList(tamanho_inicial);

  do {
    scanf("%s", comando);
    getchar();

    if (strcmp(comando, "sair") == 0) {
      destroy_arrayList(&arrayList);
      continue;
    }

    if (strcmp(comando, "tamanho") == 0) {
      printf("%d\n", size_arrayList(arrayList));
      continue;
    }

    if (strcmp(comando, "add") == 0) {
      scanf("%d %d", &chave, &valor);
      add_arrayList(arrayList, create_item(chave, valor));
      continue;
    }

    if (strcmp(comando, "sub") == 0) {
      scanf("%d %d", &pos1, &pos2);
      subArray = subArray_arrayList(arrayList, pos1, pos2);
      print_arrayList(subArray);
      destroy_arrayList(&subArray);
      continue;
    }

    if (strcmp(comando, "set") == 0) {
      scanf("%d %d %d", &pos1, &chave, &valor);
      set_arrayList(arrayList, pos1, chave, valor);
      continue;
    }

    if (strcmp(comando, "print") == 0) {
      print_arrayList(arrayList);
      continue;
    }

    if (strcmp(comando, "contem") == 0) {
      scanf("%d", &chave);
      printf("%d\n", contains_arrayList(arrayList, chave));
      continue;
    }

    if (strcmp(comando, "indice") == 0) {
      scanf("%d", &chave);
      pos1 = indexOf_arrayList(arrayList, chave);
      if (pos1 != -1) {
        printf("%d\n", indexOf_arrayList(arrayList, chave));
      }
      continue;
    }

    if (strcmp(comando, "vazia") == 0) {
      printf("%d\n", isEmpty_arrayList(arrayList));
      continue;
    }

    if (strcmp(comando, "remover") == 0) {
      scanf("%d", &pos1);
      remove_arrayList(arrayList, pos1);
      continue;
    }

    if (strcmp(comando, "get") == 0) {
      scanf("%d", &pos1);
      print_item(get_arrayList(arrayList, pos1));
      continue;
    }

  } while (strcmp(comando, "sair") != 0);

  return 0;
}
