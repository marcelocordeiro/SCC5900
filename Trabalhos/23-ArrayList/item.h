/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 02/07/2017
*/

#ifndef ITEM_H
#define ITEM_H

typedef struct {
  int key;
  int value;
} ITEM;

ITEM *create_item(int, int);
void destroy_item(ITEM *);
void print_item(ITEM *);

#endif
