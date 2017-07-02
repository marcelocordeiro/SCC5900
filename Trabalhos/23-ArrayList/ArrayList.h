/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 02/07/2017
*/

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <item.h>

#define tamanho_inicial 10

typedef struct ArrayList_str {
  ITEM **list; //lista interna de void
  int used; //tamanho ocupado na lista
  int length; //tamanho da lista interna
  struct ArrayList_str *next;
} ArrayList;

ArrayList *new_arrayList();

void add_arrayList(ArrayList *, ITEM *);

int contains_arrayList(ArrayList *, int);

ITEM *get_arrayList(ArrayList *, int);

int indexOf_arrayList(ArrayList *, int);

int isEmpty_arrayList(ArrayList *);

void remove_arrayList(ArrayList *, int);

void set_arrayList(ArrayList *, int, int, int);

int size_arrayList(ArrayList *);

ArrayList *subArray_arrayList(ArrayList *, int, int);

void destroy_arrayList(ArrayList **);

void print_arrayList(ArrayList *);

#endif
