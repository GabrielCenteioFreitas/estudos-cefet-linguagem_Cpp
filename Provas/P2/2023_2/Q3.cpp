#include <iostream>

using namespace std;

#define TAMANHO 7

void troca (int *x, int *y) {
  int aux;
  aux = *x;
  *x = *y;
  *y = aux;
}

// zero-based
void descer(int array[], int i, int qnt) {
  int dir = 2*i + 2;
  int esq = 2*i + 1;
  int maior = i;

  if (dir < qnt && array[dir] > array[i])
    maior = dir;
  if (esq < qnt && array[esq] > array[i])
    maior = esq;
  if (maior != i) {
    troca(&array[i], &array[maior]);
    descer(array, maior, qnt);
  }
}

// zero-based
void remover(int array[], int* qnt) {
  array[0] = array[(*qnt) - 1];
  (*qnt)--;
  descer(array, 0, *qnt);
}