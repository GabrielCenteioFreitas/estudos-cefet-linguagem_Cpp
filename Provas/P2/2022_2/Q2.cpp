#include <iostream>

using namespace std;

struct no {
  int info;
  struct no* prox;
};
typedef struct no* noPtr;

void inserir(noPtr* raiz, noPtr* fim) {
  noPtr novoNo = new no;
  cout << "Digite o valor: ";
  cin >> novoNo->info;

  if (!(*raiz)) {
    novoNo->prox = novoNo;
    *raiz = novoNo;
    *fim = novoNo;
  } else {
    novoNo->prox = *raiz;
    (*fim)->prox = novoNo;
    *fim = novoNo;
  }
}