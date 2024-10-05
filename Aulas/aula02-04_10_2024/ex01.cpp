#include <iostream>

using namespace std;

#define TAMANHO 50

int bubbleSwitches = 0, selectionSwitches = 0, insertionSwitches = 0,
    bubbleAccesses = 0, selectionAccesses = 0, insertionAccesses = 0;

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
      bubbleAccesses++;
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
      selectionAccesses++;
    }

    int aux = array[i];
    array[i] = array[menor];
    array[menor] = aux;
    selectionSwitches++;
  }
}

void insertionSort(int array[]) {
  for (int i = 1; i < TAMANHO; i++) {
    int j = i;

    while (j >= 1 && array[j-1] > array[j]) {
      int aux = array[j];
      array[j] = array[j-1];
      array[j-1] = aux;
      j--;
      insertionSwitches++;
      insertionAccesses++;
    }
  }
}

int main() {
  int array[TAMANHO];
  for (int i = 0; i < TAMANHO; i++) {
    cout << i+1 << "o elemento: ";
    cin >> array[i];
  }

  int bubbleSortedArray[TAMANHO], selectionSortedArray[TAMANHO], insertionSortedArray[TAMANHO];
  for (int i = 0; i < TAMANHO; i++) {
    bubbleSortedArray[i] = array[i];
    selectionSortedArray[i] = array[i];
    insertionSortedArray[i] = array[i];
  }

  bubbleSort(bubbleSortedArray);
  selectionSort(selectionSortedArray);
  insertionSort(insertionSortedArray);

  cout << "\nBubble sort: ";
  printarArray(bubbleSortedArray);
  cout << "Selection sort: ";
  printarArray(selectionSortedArray);
  cout << "Insertion sort: ";
  printarArray(insertionSortedArray);

  cout << "\nBubble switches: " << bubbleSwitches << "\n";
  cout << "Selection switches: " << selectionSwitches << "\n";
  cout << "Insertion switches: " << insertionSwitches << "\n";

  cout << "\nBubble accesses: " << bubbleAccesses << "\n";
  cout << "Selection accesses: " << selectionAccesses << "\n";
  cout << "Insertion accesses: " << insertionAccesses << "\n";

  return 0;
}