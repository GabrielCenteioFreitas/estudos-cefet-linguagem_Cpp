#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

#define TAMANHO 6

long long bubbleSwitches = 0, selectionSwitches = 0, insertionSwitches = 0;

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

void bubbleSort(int array[]) {
  for (int i = 0; i < TAMANHO-1; i++) {
    for (int j = i+1; j < TAMANHO; j++) {
      if (array[i] > array[j]) {
        int aux = array[i];
        array[i] = array[j];
        array[j] = aux;
        bubbleSwitches++;
      }
    }
  }
}

void selectionSort(int array[]) {
  for (int i = 0; i < TAMANHO-1; i++) {
    int menor = i;
    
    for (int j = i+1; j < TAMANHO; j++) {
      if (array[j] < array[menor]) {
        menor = j;
      }
    }

    int aux = array[i];
    array[i] = array[menor];
    array[menor] = aux;
    selectionSwitches++;
  }
}

void insertionSort(int array[]) {
  for (int i = 1; i < TAMANHO; i++) {
    int alvo = array[i];
    int j = i - 1;

    while (j >= 0 && alvo < array[j]) {
      array[j + 1] = array[j];
      printarArray(array);
      j--;
      insertionSwitches++;
    }

    array[j + 1] = alvo;
    printarArray(array);
    insertionSwitches++;
  }
}

int main() {
  srand(time(0));

  int array[TAMANHO] = {17, 38, 2, 7, 10, 9};
  // for (int i = 0; i < TAMANHO; i++) {
  //   array[i] = rand() % 1000 + 1;
  // }

  int bubbleSortedArray[TAMANHO], selectionSortedArray[TAMANHO], insertionSortedArray[TAMANHO];
  for (int i = 0; i < TAMANHO; i++) {
    bubbleSortedArray[i] = array[i];
    selectionSortedArray[i] = array[i];
    insertionSortedArray[i] = array[i];
  }

  auto inicio1 = std::chrono::high_resolution_clock::now();
  bubbleSort(bubbleSortedArray);
  auto fim1 = std::chrono::high_resolution_clock::now();
    
  auto inicio2 = std::chrono::high_resolution_clock::now();
  selectionSort(selectionSortedArray);
  auto fim2 = std::chrono::high_resolution_clock::now();
  
  auto inicio3 = std::chrono::high_resolution_clock::now();
  insertionSort(insertionSortedArray);
  auto fim3 = std::chrono::high_resolution_clock::now();

  cout << "\nBubble switches: " << bubbleSwitches << "\n";
  cout << "Selection switches: " << selectionSwitches << "\n";
  cout << "Insertion switches: " << insertionSwitches << "\n";

  auto duracao1 = std::chrono::duration_cast<std::chrono::milliseconds>(fim1 - inicio1);
  cout << "O Bubble sort demorou " << duracao1.count() << " millissegundos.\n";

  auto duracao2 = std::chrono::duration_cast<std::chrono::milliseconds>(fim2 - inicio2);
  cout << "O Selection sort demorou " << duracao2.count() << " millissegundos.\n";

  auto duracao3 = std::chrono::duration_cast<std::chrono::milliseconds>(fim3 - inicio3);
  cout << "O Insertion sort demorou " << duracao3.count() << " millissegundos.\n";

  return 0;
}