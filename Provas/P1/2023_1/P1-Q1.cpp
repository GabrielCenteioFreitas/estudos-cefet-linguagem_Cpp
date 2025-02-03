#include <iostream>

using namespace std;

struct contato {
  int num;
  struct contato* prox;
};
typedef struct contato* contatoPtr;

contatoPtr topo = NULL;
contatoPtr ult = NULL;

void adicionar() {
  int num;
  cin >> num;

  contatoPtr novaContato;
  novaContato = new contato;
  novaContato->num = num;
  novaContato->prox = NULL;

  if (!topo) {
    topo = novaContato;
    ult = novaContato;
  } else {
    ult->prox = novaContato;
    ult = novaContato;
  }
}

void remover() {
  if (!topo) return;

  contatoPtr temp = topo;
  topo = topo->prox;
  delete temp;
}