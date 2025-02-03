#include <iostream>

using namespace std;

struct peca {
  int num;
  struct peca* prox;
};
typedef struct peca* pecaPtr;

pecaPtr topo = NULL;
pecaPtr ult = NULL;

void desmontar() {
  int num;
  cin >> num;

  pecaPtr novaPeca;
  novaPeca = new peca;
  novaPeca->num = num;
  novaPeca->prox = NULL;

  if (!topo) {
    topo = novaPeca;
    ult = novaPeca;
  } else {
    ult->prox = novaPeca;
    ult = novaPeca;
  }
}

void remontar() {
  if (!topo) return;

  pecaPtr temp = topo;
  topo = topo->prox;
  delete temp;
}