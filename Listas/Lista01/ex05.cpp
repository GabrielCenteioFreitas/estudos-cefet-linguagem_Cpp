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

void dividir(noPtr* topo, int valor) {
  if (!*topo) return;

  noPtr topo2 = NULL, aux = *topo;
  while(aux && aux->valor != valor) {
    aux = aux->prox;
  }
  topo2 = aux->prox;
  aux->prox = NULL;

  printf("----- Lista 1 -----\n");
  listar(*topo);
  printf("\n----- Lista 2 -----\n");
  listar(topo2);
}

int main() {
  noPtr topo = NULL;

  push(&topo, 6);
  push(&topo, 5);
  push(&topo, 4);
  push(&topo, 3);
  push(&topo, 2);
  push(&topo, 1);
  
  dividir(&topo, 1);

  return 0;
}