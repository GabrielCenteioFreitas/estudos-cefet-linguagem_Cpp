#include <iostream>

using namespace std;

#define TAMANHO 5

void printarArray(int array[]) {
  cout << "[";
  for (int i = 0; i < TAMANHO; i++) {
    cout << array[i];
    if (i != TAMANHO-1) {
      cout << ", ";
    }
  }
  cout << "]" << endl;
}

void intercala(int array[], int inicio, int fim, int meio) {
  int i, aux [TAMANHO], posLivre = inicio, inicioA1 = inicio, inicioA2 = meio + 1;

  while (inicioA1 <= meio && inicioA2 <= fim) {
    if (array[inicioA1] > array[inicioA2]) {
      aux[posLivre] = array[inicioA2];
      inicioA2++;
    } else {
      aux[posLivre] = array[inicioA1];
      inicioA1++;
    }

    posLivre++;
  }

  for (i = inicioA1; i <= meio; i++) {
    aux[posLivre] = array[i];
    posLivre++;
  }
  for (i = inicioA2; i <= fim; i++) {
    aux[posLivre] = array[i];
    posLivre++;
  }

  for (i = inicio; i <= fim; i++) {
    array[i] = aux[i];
  }
}

void mergesort(int array[], int inicio, int fim) {
  int meio;
  if (inicio < fim) {
    meio = (inicio + fim)/2;
    mergesort(array, inicio, meio);
    mergesort(array, meio + 1, fim);
    intercala(array, inicio, fim, meio);
  }
}

int main() {
  int array[TAMANHO] = {10, 7, 5, 8, 4};
  printarArray(array);

  mergesort(array, 0, TAMANHO-1);

  printarArray(array);
}