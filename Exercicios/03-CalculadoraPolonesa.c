/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 03/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack_str {
  double number;
  struct stack_str *next;
} stack;

double myPop(stack **myStack) {
  double number;

  if (*myStack == NULL) {
    return 0;
  }

  number = (*myStack)->number;
  *myStack = (*myStack)->next;

  return number;
}

void myPush(stack **myStack, double number) {
  stack *newStack;

  newStack = malloc(sizeof(stack));
  newStack->number = number;
  newStack->next = *myStack;

  *myStack = newStack;
}

void printStack(stack *myStack) {
  while (myStack) {
    printf("%.1lf  ", myStack->number);
    myStack = myStack->next;
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  stack *myStack = NULL;
  char input[1000], *symbol;
  double result, aux1, aux2;

  scanf("%[^\n]s", input);

  symbol = strtok(input, " ");

  while (symbol != NULL) {
    if (strlen(symbol) > 1) {
      myPush(&myStack, atof(symbol));
    }
    else {
      switch (symbol[0]) {
        case '+':
          result = (myPop(&myStack) + myPop(&myStack));
          myPush(&myStack, result);
          break;
        case '-':
          aux1 = myPop(&myStack);
          aux2 = myPop(&myStack);
          result = (aux2 - aux1);
          myPush(&myStack, result);
          break;
        case '*':
          result = (myPop(&myStack) * myPop(&myStack));
          myPush(&myStack, result);
          break;
        case '/':
          aux1 = myPop(&myStack);
          aux2 = myPop(&myStack);
          result = (aux2 / aux1);
          myPush(&myStack, result);
          break;
      }
    }
    symbol = strtok(NULL, " ");
  }

  printf("%.6lf\n", result);

  return 0;
}
