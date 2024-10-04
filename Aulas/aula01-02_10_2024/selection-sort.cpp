#include <iostream>

void sort(int array[], int tamanho) {
  for (int i = 0; i < tamanho-1; i++) {
    int maior = i;
    
    for (int j = i+1; j < tamanho; j++) {
      if (array[j] > array[maior]) {
        maior = j;
      }
    }

    int aux = array[i];
    array[i] = array[maior];
    array[maior] = aux;
  }
}

int main() {
  int tamanho;
  std::cout << "Quantos elementos no array? ";
  std::cin >> tamanho;

  int array[tamanho] = {};
  for (int i = 0; i < tamanho; i++) {
    std::cout << i+1 << "o elemento: ";
    std::cin >> array[i];
  }

  sort(array, tamanho);

  std::cout << "Array ordenado: [";
  for (int i = 0; i < tamanho; i++) {
    std::cout << array[i];
    if (i != tamanho-1) {
      std::cout << ", ";
    }
  }
  std::cout << "]" << std::endl;
}