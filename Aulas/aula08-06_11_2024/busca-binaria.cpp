#include <iostream>

#define T 7

using namespace std;

int binaria(int A[], int x, int inicioParam, int fimParam) {
  int inicio = inicioParam;
  int fim = fimParam;
  int meio;
  while (inicio <= fim) {
    meio = (inicio+fim)/2;

    if (x == A[meio]) {
      return meio;
    }

    if (x < A[meio]) {
      fim = meio - 1;
    } else {
      inicio = meio + 1;
    }
  }
  return -1;
}

int main() {
  int num, x, A[T]={9, 10, 12, 15, 25, 30, 50};
  cout << "Numero a ser buscado: ";
  cin >> num;

  x = binaria(A, num, 0, T-1);
  if (x > -1) {
    cout << "Numero encontrado na " << x+1 << "a posicao" << endl;
  } else {
    cout << "Numero nao encontrado" << endl;
  }
}