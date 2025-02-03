#include <iostream>

using namespace std;

struct no {
  int info;
  struct no* esq;
  struct no* dir;
};
typedef struct no* noPtr;

void listarPreOrdem(noPtr p) {
  if (p) {
    cout << p->info << " ";
    listarPreOrdem(p->esq);
    listarPreOrdem(p->dir);
  }
}