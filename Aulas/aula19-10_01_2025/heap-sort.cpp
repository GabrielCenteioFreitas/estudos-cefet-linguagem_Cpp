#include <iostream>

using namespace std;

#define TAMANHO 10

void printarArray(int array[], int qnt) {
  if (!qnt) {
    printf("Lista vazia.\n");
    return;
  }

  printf("Lista: [");
  for (int i = 0; i < qnt-1; i++) {
    printf("%d, ", array[i]);
  }
  printf("%d]\n", array[qnt-1]);
}

void troca(int *a, int * b) {
  int aux;
  aux = *a;
  *a = *b;
  *b = aux;
}

void descer(int A[], int numPos, int qnt) {
  int filhoDir = 2*numPos + 2;
  int filhoEsq = 2*numPos + 1;
  int maiorPos = numPos;
  if (filhoDir <= qnt && A[filhoDir] > A[numPos])
    maiorPos = filhoDir;
  if (filhoEsq <= qnt && A[filhoEsq] > A[maiorPos])
    maiorPos = filhoEsq;
  if (maiorPos != numPos) {
    troca(&A[numPos], &A[maiorPos]);
    descer(A, maiorPos, qnt);
  }
}

void heap(int A[], int qnt) {
  for (int i = (qnt / 2); i >= 0; i--)
    descer(A, i, qnt - 1);
}

void heapsort(int A[], int qnt) {
  int i;

  printarArray(A, TAMANHO);
  heap(A, qnt);

  for (i = qnt-1; i >= 1; i--) {
    printarArray(A, TAMANHO);
    troca(&A[0], &A[i]);
    descer(A, 0, i-1);
  }
}

int main() {
  int array[TAMANHO] = {50, 2, 75, 8, 10, 6, 15, 4, 9, 3};

  heapsort(array, TAMANHO);
  printarArray(array, TAMANHO);

  return 0;
}