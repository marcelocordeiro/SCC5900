#ifndef ITEM_H
#define ITEM_H

//representa o item armazenado
typedef struct {
  int chave;
  int valor;
} ITEM;

ITEM *criar_item(int chave, int valor);
void apagar_item(ITEM *item);
void imprimir_item(ITEM *item);

#endif
