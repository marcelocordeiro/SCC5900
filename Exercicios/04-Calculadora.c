/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 26/04/2017
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
  float num1, num2, resultado;
  char operador;

  scanf("%f", &num1);

  scanf(" %c", &operador);

  scanf("%f", &num2);

  switch (operador) {
    case '+':
      resultado = num1 + num2;
      break;
    case '-':
      resultado = num1 - num2;
      break;
    case '*':
      resultado = num1 * num2;
      break;
    case '/':
      resultado = num1 / num2;
      break;
    case '%':
      resultado = (num1 * 100) / num2;
      break;
  }

  printf("%.6f", resultado);

  return 0;
}
