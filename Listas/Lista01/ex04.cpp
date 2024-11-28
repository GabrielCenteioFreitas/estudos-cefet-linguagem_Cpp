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

void retirar(noPtr* topo, int valor) {
  if (!*topo) return;

  while (*topo && (*topo)->valor == valor) {
    pop(topo);
  }

  noPtr ant = *topo, aux = (*topo) ? (*topo)->prox : NULL;
  while (aux) {
    if (aux->valor == valor) {
      ant->prox = aux->prox;
      delete aux;
      aux = ant->prox;
    } else {
      ant = aux;
      aux = aux->prox;
    }
  }

  listar(*topo);
}

int main() {
  noPtr topo = NULL;

  push(&topo, 5);
  push(&topo, 8);
  push(&topo, 7);
  push(&topo, 3);
  push(&topo, 1);
  push(&topo, 7);
  push(&topo, 2);
  push(&topo, 4);
  push(&topo, 7);
  push(&topo, 7);
  push(&topo, 7);
  
  retirar(&topo, 7);

  return 0;
}