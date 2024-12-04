void bubbleSort(int array[]) {
  int aux;
  for (int i = 40; i > 0; i--) {
    for (int j = 0; j < i-1; j++) {
      if (array[j] < array[j+1]) {
        aux = array[j];
        array[j] = array[j+1];
        array[j+1] = aux;
      }
    }
  }
}