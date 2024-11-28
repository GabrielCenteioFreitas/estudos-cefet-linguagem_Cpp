#include <iostream>

using namespace std;

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

struct no {
  int valor;
  struct no *prox;
};
typedef struct no* noPtr;

void push(noPtr* topo, int valor) {
  noPtr novoNo = new no;
  novoNo->valor = valor;
  novoNo->prox = *topo;
  *topo = novoNo;
}

void pop(noPtr* topo) {
  if (!*topo) return;

  noPtr temp = *topo;
  *topo = (*topo)->prox;
  delete temp;
}

void listar(noPtr topo) {
  if (!topo) return;

  int i = 0;
  for (noPtr aux = topo; aux; i++, aux = aux->prox) {
    printf("%do elemento:\n", i+1);
    printf("  Valor: %d\n", aux->valor);
    printf("  Endereco: %p\n", aux);
    printf("  Endereco do prox: %p\n", aux->prox);
  }
}

void intercalar(noPtr topo1, noPtr topo2) {
  noPtr novoTopo = NULL;

  noPtr aux1 = topo1, aux2 = topo2;

  int i = 0;
  while(aux1 || aux2) {
    if (i % 2 == 0) {
      push(&novoTopo, aux1->valor);
      aux1 = aux1->prox;
    } else {
      push(&novoTopo, aux2->valor);
      aux2 = aux2->prox;
    }

    i++;
  }

  listar(novoTopo);
}

int main() {
  noPtr topo1 = NULL, topo2 = NULL;

  push(&topo1, 30);
  push(&topo1, 20);
  push(&topo1, 10);
  push(&topo2, 60);
  push(&topo2, 50);
  push(&topo2, 40);
  
  intercalar(topo1, topo2);
  
  return 0;
}