#include <iostream>

using namespace std;

struct robo {
  int num;
  struct robo* prox;
};
typedef struct robo* roboPtr;

roboPtr topo = NULL;
roboPtr ult = NULL;

void adicionarLocal() {
  roboPtr novoLocal = new robo;
  cin >> novoLocal->num;
  novoLocal->prox = NULL;

  if (!topo) {
    topo = novoLocal;
    ult = novoLocal;
  } else {
    ult->prox = novoLocal;
    ult = novoLocal;
  }
}

void limparLocal() {
  roboPtr temp;
  if (topo) {
    temp = topo;
    topo = topo->prox;
    delete temp;
  }
}