#include <iostream>

using namespace std;

bool buscaBinaria(int array[], int x) {
  int inicio = 0;
  int fim = 99;
  int meio;

  while (inicio <= fim) {
    meio = (inicio + fim) / 2;

    if (x == array[meio]) {
      cout << array[meio] << "\n";
      return true;
    }

    if (x < array[meio]) {
      fim = meio - 1;
    } else {
      inicio = meio + 1;
    }
  }

  return false;
}