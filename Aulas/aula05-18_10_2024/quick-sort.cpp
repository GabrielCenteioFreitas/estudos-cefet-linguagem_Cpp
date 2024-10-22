#include <iostream>

using namespace std;

#define TAMANHO 7

void printarArray(int array[], float n) {
  cout << n << ": [";
  for (int i = 0; i < TAMANHO; i++) {
    cout << array[i];
    if (i != TAMANHO-1) {
      cout << ", ";
    }
  }
  cout << "]" << endl;
}

void troca (int * x, int * y) {
  int aux;
  aux = *x;
  *x = *y;
  *y = aux;
}

void quickSort(int A[], int inicio, int fim) {
  int i, j, chave;
  if (fim - inicio < 2) { // I, ?, F
    if ((fim - inicio) == 1) { // estão colados
      if (A[inicio] > A[fim]) { // se o da esquerda for maior que o da direita
        printarArray(A, 1.1);
        troca(&A[inicio], &A[fim]);
        printarArray(A, 1.2);
      }
    }
  } else {
    i = inicio;
    j = fim;
    chave = A[inicio];

    while (j > i) {
      i++; // pegar segundo elemento pq o primeiro é a chave

      cout << "i - " << i << "\n";
      while(A[i] < chave) { // já ta do lado certo, só aumenta
        i++;
        cout << "i - " << i << "\n";
      }

      cout << "j - " << j << "\n";
      while(A[j] > chave) { // já ta do lado certo, só diminui
        j--;
        cout << "j - " << j << "\n";
      }

      cout << "2.1: i - " << i << "; j - " << j << "\n";
      if (j > i) { // se ainda existem elementos nos dois lados q estão no lado errado
        printarArray(A, 2.2);
        troca(&A[i], &A[j]);
        printarArray(A, 2.3);
      }
    }

    printarArray(A, 3.1);
    troca(&A[inicio], &A[j]); // botar o chave no meio
    printarArray(A, 3.2);
    quickSort(A, inicio, j - 1); // quick sort na esquerda
    printarArray(A, 3.3);
    quickSort(A, j + 1, fim); // quick sort na direita
  }
}


int main() {
  int array[TAMANHO] = {5, 9, 1, 2, 0, 3, 8};

  printarArray(array, 0);
  quickSort(array, 0, TAMANHO-1);
  printarArray(array, 9999);

  return 0;
}