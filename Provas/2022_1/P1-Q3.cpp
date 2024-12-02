void selectionSort(int array[], int tamanho) {
  int posicaoDaChave = 0, aux;
  for (int i = 0; i < tamanho - 1; i++) {
    posicaoDaChave = i;
    for (int j = i + 1; j < tamanho; j++) {
      if (array[j] < array[posicaoDaChave]) {
        posicaoDaChave = j;
      }
    }
    aux = array[posicaoDaChave];
    array[posicaoDaChave] = array[i];
    array[i] = aux;
  }
}