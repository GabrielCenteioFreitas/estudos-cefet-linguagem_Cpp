#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>

#define TAMANHO 100000

using namespace std;

void troca (int * x, int * y) {
  int aux;
  aux = *x;
  *x = *y;
  *y = aux;
}

void quickSort(int A[], int inicio, int fim) {
  int i, j, chave;
  if (fim - inicio < 2) {
    if ((fim - inicio) == 1) {
      if (A[inicio] > A[fim]) {
        troca(&A[inicio], &A[fim]);
      }
    }
  } else {
    i = inicio;
    j = fim;
    chave = A[inicio];

    while (j > i) {
      i++;

      while(A[i] < chave) {
        i++;
      }

      while(A[j] > chave) {
        j--;
      }

      if (j > i) {
        troca(&A[i], &A[j]);
      }
    }

    troca(&A[inicio], &A[j]);
    quickSort(A, inicio, j - 1);
    quickSort(A, j + 1, fim);
  }
}

int buscaBinaria(int A[], int x, int inicio, int fim) {
  if (inicio == fim) {
    return 0;
  }

  int meio = (inicio+fim)/2;
  if (x == A[meio]) {
    return meio;
  }

  if (x < A[meio]) {
    return buscaBinaria(A, x, 0, meio);
  }

  return buscaBinaria(A, x, meio+1, fim);
}

int buscaSequencial (int A[], int x) {
  bool achei = false;
  int i = 0;
  while (!achei && i < TAMANHO) {
    if(A[i] == x) {
      achei = true;
      return i;
    } else i++;
  }

  return -1;
}

int main() {
  srand(time(0));
  bool randomArray = true;

  int array[TAMANHO];
  for (int i = 0; i < TAMANHO; i++) {
    if (randomArray) {
      array[i] = rand() % (TAMANHO*10);
    } else {
      array[i] = i;
    }
  }
  
  int numToFind = array[random() % TAMANHO];

  cout << "O número que está sendo buscado é " << numToFind << endl;
  
  auto inicioSequencial = chrono::high_resolution_clock::now();
  buscaSequencial(array, numToFind);
  auto fimSequencial = chrono::high_resolution_clock::now();

  auto inicioOrdenacao = chrono::high_resolution_clock::now();
  if (randomArray) {
    quickSort(array, 0, TAMANHO);
  }
  auto fimOrdenacao = chrono::high_resolution_clock::now();
  buscaBinaria(array, numToFind, 0, TAMANHO);
  auto fimBinaria = chrono::high_resolution_clock::now();

  auto duracaoSequencial = chrono::duration_cast<chrono::microseconds>(fimSequencial - inicioSequencial);
  cout << "A busca sequencial demorou " << duracaoSequencial.count() << " microssegundos.\n";

  auto duracaoBinariaBusca = chrono::duration_cast<chrono::microseconds>(fimBinaria - fimOrdenacao);
  cout << "A busca binaria demorou " << duracaoBinariaBusca.count() << " microssegundos BUSCANDO.\n";
  auto duracaoBinariaOrdenacao = chrono::duration_cast<chrono::microseconds>(fimOrdenacao - inicioOrdenacao);
  cout << "A busca binaria demorou " << duracaoBinariaOrdenacao.count() << " microssegundos ORDENANDO.\n";
}