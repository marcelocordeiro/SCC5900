/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 02/07/2017
*/

#include <stdio.h>
#include <item.h>

int binary_search(ITEM **vector, int start, int end, int key) {
	int middle;
	if (start > end) {
    return -1;
  }
	middle = (start+end)/2;
	if (vector[middle]->key == key) {
		return middle;
	}
  else {
    if (key > vector[middle]->key) {
		    return binary_search(vector, middle+1, end, key);
	  }
    else {
      if (key < vector[middle]->key) {
		    return binary_search(vector, start, middle-1, key);
	    }
    }
  }
}
