#include <iostream>

using namespace std;

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

void troca(int* num1, int* num2) {
  int aux = *num1;
  *num1 = *num2;
  *num2 = aux;
}

void subir(int array[], int i, int qnt) {
  int j = (i-1)/2;
  if (j >= 0 && array[i] > array[j]) {
    troca(&array[i], &array[j]);
    printarArray(array, qnt);
    subir(array, j, qnt);
  }
}

void descer(int array[], int i, int qnt) {
  int dir = 2*i + 2;
  int esq = 2*i + 1;
  int maior = i;
  if (dir <= qnt && array[dir] > array[i])
    maior = dir;
  if (esq <= qnt && array[esq] > array[maior])
    maior = esq;
  if (maior != i) {
    troca(&array[i], &array[maior]);
    printarArray(array, qnt);
    descer(array, maior, qnt);
  }
}

void inserir(int array[], int valor, int* qnt) {
  array[*qnt] = valor;
  (*qnt)++;
  printarArray(array, *qnt);
  subir(array, (*qnt)-1, *qnt);
}

void remover(int array[], int* qnt) {
  array[0] = array[(*qnt)-1];
  (*qnt)--;
  printarArray(array, *qnt);
  descer(array, 0, *qnt);
}

int main() {
  int qnt = 8;
  printf("-------------------------------------\n");
  int array1[qnt] = {92, 85, 90, 47, 91, 34, 20, 46};
  printarArray(array1, qnt);
  subir(array1, 4, qnt);
  printf("\n-------------------------------------\n");
  int array2[qnt] = {92, 85, 90, 47, 93, 34, 20, 46};
  printarArray(array2, qnt);
  subir(array2, 4, qnt);
  printf("\n-------------------------------------\n");
  int array3[qnt] = {92, 85, 90, 47, 19, 34, 20, 46};
  printarArray(array3, qnt);

  return 0;
}