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

ITEM *criar_item(int chave, int valor);
void apagar_item(ITEM *item);
void imprimir_item(ITEM *item);

#endif
