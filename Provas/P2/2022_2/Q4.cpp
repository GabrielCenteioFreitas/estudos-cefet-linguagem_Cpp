#include <iostream>

using namespace std;

struct no {
  int info;
  struct no* esq;
  struct no* dir;
};
typedef struct no* noPtr;

void mostrarNosDeGrauDois(noPtr p) {
  if (!p) return;

  if (p->esq && p->dir) {
    cout << p->info << endl;
  }

  mostrarNosDeGrauDois(p->esq);
  mostrarNosDeGrauDois(p->dir);
}