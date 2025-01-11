#include <iostream>

using namespace std;

#define TAMANHO 7

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"

void printarArray(int array[], int qnt, int elemVerm, int elemAzul1, int elemAzul2, int primeiroVerde) {
  string cor;
  if (!qnt) {
    printf("Lista vazia.\n");
    return;
  }

  printf(" [");
  for (int i = 0; i < qnt; i++) {
    cor = i == elemAzul1 || i == elemAzul2 ? BLUE : i == elemVerm ? RED : i >= primeiroVerde ? GREEN : "";
    cout << cor;
    printf("%d", array[i]);
    printf(RESET);
    if (i != qnt-1)
      printf(", ");
    else
      printf("]\n");
  }
}

void troca(int *a, int * b) {
  int aux;
  aux = *a;
  *a = *b;
  *b = aux;
}

int descer(int A[], int numPos, int qnt) {
  int filhoDir = 2*numPos + 2;
  int filhoEsq = 2*numPos + 1;
  int maiorPos = numPos;
  int posFinal = numPos;
  if (filhoDir <= qnt && A[filhoDir] > A[numPos])
    maiorPos = filhoDir;
  if (filhoEsq <= qnt && A[filhoEsq] > A[maiorPos])
    maiorPos = filhoEsq;
  if (maiorPos != numPos) {
    troca(&A[numPos], &A[maiorPos]);
    posFinal = descer(A, maiorPos, qnt);
  }

  return posFinal;
}

void heap(int A[], int qnt) {
  for (int i = (qnt / 2); i >= 0; i--)
    descer(A, i, qnt - 1);
}

void heapsort(int A[], int qnt) {
  int posAposDescida;

  printf("Array inicial:\n");
  printarArray(A, TAMANHO, -1, -1, -1, TAMANHO);
  heap(A, qnt);
  printf("Array pós heap:\n");
  printarArray(A, TAMANHO, -1, -1, -1, TAMANHO);

  for (int i = qnt-1; i >= 1; i--) {
    printf("Trocando o %d com o %d:\n", A[0], A[i]);
    printarArray(A, TAMANHO, -1, 0, i, i+1);
    troca(&A[0], &A[i]);
    printarArray(A, TAMANHO, -1, 0, i, i+1);
    printf("Descendo o %d:\n", A[0]);
    printarArray(A, TAMANHO, 0, -1, -1, i);
    posAposDescida = descer(A, 0, i-1);
    printarArray(A, TAMANHO, posAposDescida, -1, -1, i);
  }
}

int main() {
  int array[TAMANHO] = {80, 35, 20, 60, 42, 36, 85};

  heapsort(array, TAMANHO);
  printf("Array ordenado:\n");
  printarArray(array, TAMANHO, -1, -1, -1, 0);

  return 0;
}