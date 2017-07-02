/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 02/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <item.h>

ITEM *create_item(int key, int value) {
  ITEM *new_item;
  new_item = malloc(sizeof(ITEM));
  new_item->key = key;
  new_item->value = value;
  return new_item;
}

void destroy_item(ITEM *item) {
  if (item != NULL) {
    free(item);
  }
}

void print_item(ITEM *item) {
  if (item != NULL) {
    printf("%d/%d\n", item->key, item->value);
  }
}
