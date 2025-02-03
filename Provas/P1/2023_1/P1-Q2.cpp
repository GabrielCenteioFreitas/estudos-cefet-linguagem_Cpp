void bubbleSort(int array[], int tamanho) {
  int aux;
  for (int i = 0; i < tamanho-1; i++) {
    for (int j = i + 1; j < tamanho; j++) {
      if (array[i] < array[j]) {
        aux = array[i];
        array[i] = array[j];
        array[j] = aux;
      }
    }
  }
}