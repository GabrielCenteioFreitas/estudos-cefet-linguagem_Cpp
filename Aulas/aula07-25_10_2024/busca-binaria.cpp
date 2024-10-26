#include <iostream>

#define T 7

using namespace std;

int binaria(int A[], int x, int inicio, int fim) {
  if (inicio == fim) {
    return 0;
  }

  int meio = (inicio+fim)/2;
  if (x == A[meio]) {
    return meio;
  }

  if (x < A[meio]) {
    return binaria(A, x, 0, meio);
  }

  return binaria(A, x, meio+1, fim);
}

int main() {
  int num, x, A[T]={9, 10, 12, 15, 25, 30, 50};
  cout << "Numero a ser buscado: ";
  cin >> num;

  x = binaria(A, num, 0, T);
  if (x) {
    cout << "Numero encontrado na " << x+1 << "a posicao" << endl;
  } else {
    cout << "Numero nao encontrado" << endl;
  }
}