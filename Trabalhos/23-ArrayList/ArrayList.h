/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 02/07/2017
*/

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <item.h>

typedef struct node_str {
  ITEM **list; //lista interna de void
  int used; //tamanho ocupado na lista
  int length; //tamanho da lista interna
  struct node_str *next;
} node;

typedef struct {
  node *start;
} ArrayList;

//Cria a ArrayList e aloca toda memória necessaria
ArrayList *new_arrayList();

//adiciona elemento ao arraylist
int add_arrayList(ArrayList *arrayList, ITEM *element);

//verifica no arraylist se existe um elemento com a chave informada
int contains_arrayList(ArrayList *arrayList, int chave);

//recupera um ITEM na posição informada
ITEM *get_arrayList(ArrayList *arrayList, int pos);

//retorna qual a posicao do primeiro elemento com a chave informada
int indexOf_arrayList(ArrayList *arrayList, int chave);

//verifica se o arraylist esta vazio
int isEmpty_arrayList(ArrayList *arrayList);

//remove um elemento do arraylist
int remove_arrayList(ArrayList *arrayList, int pos);

//modifica um elemento do arraylist
int set_arrayList(ArrayList *arrayList, int pos, ITEM *element);

//retorna o tamanho total do arraylist
int size_arrayList(ArrayList *arrayList);

//recupera um novo subarray no intervalo [beginIndex, endIndex[
ArrayList *subArray_arrayList(ArrayList *arrayList, int beginIndex, int endIndex);

//desaloca memória alocada pelo arraylist
int destruct_arrayList(ArrayList **arrayList);

//imprime toda a lista
void print_arrayList(ArrayList *arrayList);

#endif
