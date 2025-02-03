#include <iostream>

using namespace std;

struct no {
  int info;
  struct no* esq;
  struct no* dir;
};
typedef struct no* noPtr;

int somarNos(noPtr p) {
  if (!p) return 0;
  return somarNos(p->esq) + somarNos(p->dir) + p->info;
}

void somatorio(noPtr raiz) {
  int resultado = somarNos(raiz);
  cout << resultado;
}