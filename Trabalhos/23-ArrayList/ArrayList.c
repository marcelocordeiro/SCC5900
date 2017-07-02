/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 02/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <item.h>
#include <ArrayList.h>

//Cria a ArrayList e aloca toda memória necessaria
ArrayList *new_arrayList(int length) {
  ArrayList *arrayList;
  arrayList = calloc(1, sizeof(ArrayList));
  arrayList->length = length;
  return arrayList;
}

//adiciona elemento ao arraylist
void add_arrayList(ArrayList *arrayList, ITEM *element) {
  ArrayList *aux;
  ITEM *aux_item;

  for (aux = arrayList; aux != NULL; aux = aux->next) {
    if (aux->used == 0) {
      aux->list = malloc(sizeof(ITEM*));
      aux->list[aux->used] = element;
      aux->used++;
      return;
    }
    if ((aux->list[aux->used-1]->key > element->key) || (aux->used < aux->length)) {
      if ((aux->used >= aux->length) && (aux->next == NULL)) {
        aux->next = new_arrayList(aux->length * 2);
        aux->next->list = malloc(sizeof(ITEM*));
        aux->next->list[0] = aux->list[aux->used-1];
        aux->next->used++;
        aux->used--;
      }
      if (aux->used < aux->length) {
        aux->list = realloc(aux->list, (aux->used + 1) * sizeof(ITEM*));
        for (int i = 0; i < aux->used; i++) {
          if (aux->list[i]->key > element->key) {
            for (int j = (aux->used - 1); j >= i; j--) {
              aux->list[j+1] = aux->list[j];
            }
            aux->list[i] = element;
            aux->used++;
            return;
          }
        }
        aux->list[aux->used] = element;
        aux->used++;
        return;
      }
      else {
        aux_item = aux->list[aux->used-1];
        aux->used--;
        add_arrayList(aux, element);
        add_arrayList(aux->next, aux_item);
        return;
      }
    }
    else {
      if (aux->next == NULL) {
        aux->next = new_arrayList(aux->length * 2);
      }
    }
  }
}

//verifica no arraylist se existe um elemento com a chave informada
int contains_arrayList(ArrayList *arrayList, int key) {
  return indexOf_arrayList(arrayList, key) == -1 ? 0 : 1;
}

//recupera um ITEM na posição informada
ITEM *get_arrayList(ArrayList *arrayList, int pos) {
  ArrayList *aux;
  int count = -1;

  for (aux = arrayList; aux != NULL; aux = aux->next) {
    count += aux->used;
    if (count >= pos) {
      count -= aux->used;
      return aux->list[pos - count - 1];
    }
  }

  return NULL;
}

//retorna qual a posicao do primeiro elemento com a chave informada
int indexOf_arrayList(ArrayList *arrayList, int key) {
  ArrayList *aux;
  int count = 0;

  for (aux = arrayList; aux != NULL; aux = aux->next) {
    count += aux->used;
    if (aux->list[aux->used-1]->key >= key) {
      count -= aux->used;
      return (count + binary_search(aux->list, 0, aux->used, key));
    }
  }

  return -1;
}

//verifica se o arraylist esta vazio
int isEmpty_arrayList(ArrayList *arrayList) {
  return arrayList->list == NULL ? 1 : 0;
}

//remove um elemento do arraylist
void remove_arrayList(ArrayList *arrayList, int pos) {
  ArrayList *aux;
  int index, count = -1;

  for (aux = arrayList; aux != NULL; aux = aux->next) {
    count += aux->used;
    if (count >= pos) {
      count -= aux->used;
      index = pos - count - 1;
      destroy_item(aux->list[index]);
      for (int i = index; i < (aux->used - 1); i++) {
        aux->list[i] = aux->list[i+1];
      }
      while (aux->next != NULL) {
        aux->list[aux->used - 1] = aux->next->list[0];
        aux = aux->next;
        for (int i = 0; i < (aux->used - 1); i++) {
          aux->list[i] = aux->list[i+1];
        }
      }
      aux->used--;
      return;
    }
  }
}

//modifica um elemento do arraylist
void set_arrayList(ArrayList *arrayList, int pos, int key, int value) {
  remove_arrayList(arrayList, pos);
  add_arrayList(arrayList, create_item(key, value));
}

//retorna o tamanho total do arraylist
int size_arrayList(ArrayList *arrayList) {
  ArrayList *aux;
  int count = 0;

  for (aux = arrayList; aux != NULL; aux = aux->next) {
    count += aux->used;
  }

  return count;
}

//recupera um novo subarray no intervalo [beginIndex, endIndex[
ArrayList *subArray_arrayList(ArrayList *arrayList, int beginIndex, int endIndex) {
  ArrayList *subArray;
  ITEM *new_item, *aux;

  subArray = new_arrayList(tamanho_inicial);

  for (int i = beginIndex; i < endIndex; i++) {
    aux = get_arrayList(arrayList, i);
    new_item = create_item(aux->key, aux->value);
    add_arrayList(subArray, new_item);
  }

  return subArray;
}

//desaloca memória alocada pelo arraylist
void destroy_arrayList(ArrayList **arrayList) {
  while (*arrayList != NULL) {
    for (int i = 0; i < (*arrayList)->used; i++) {
      destroy_item((*arrayList)->list[i]);
    }
    free((*arrayList)->list);
    free(*arrayList);
    *arrayList = (*arrayList)->next;
  }
}

//imprime toda a lista
void print_arrayList(ArrayList *arrayList) {
  ArrayList *aux;
  int count = 0;

  for (aux = arrayList; aux != NULL; aux = aux->next) {
    for (int i = 0; i < aux->used; i++) {
      printf("%d: ", count);
      print_item(aux->list[i]);
      count++;
    }
    printf("\n\n");
  }
}
