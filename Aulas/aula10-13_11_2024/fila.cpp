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

noPtr topo = NULL;
noPtr ult = NULL;

void saida() {
  char caractere;
  printf("\nDigite qualquer caractere para voltar ao menu ");
  cin >> caractere;
}

bool listaVazia() {
  if (!topo) {
    return true;
  }

  return false;
}

void enqueue(int valor) {
  noPtr novoNo;
  novoNo = (noPtr) malloc (sizeof (struct no));
  novoNo->valor = valor;
  novoNo->prox = NULL;

  if (listaVazia()) {
    topo = novoNo;
    ult = novoNo;
  } else {
    ult->prox = novoNo;
    ult = novoNo;
  }
  printf("Elemento de valor %d foi adicionado ao final da fila!\n", valor);
  saida();
}

void dequeue() {
  if (listaVazia()) {
    printf("A lista esta vazia\n");
    saida();
    return;
  }

  printf("Elemento de valor %d removido!\n", topo->valor);
  topo = topo->prox;
  saida();
}

void listar() {
  if (listaVazia()) {
    printf("A lista esta vazia\n");
    saida();
    return;
  }

  noPtr aux = topo;
  int i = 0;
  while (aux->prox) {
    printf("%do elemento:\n  Valor: %d\n  Endereco: %lu\n  Endereco do prox: %lu\n", i+1, aux->valor, aux, aux->prox);
    aux = aux->prox;
    i++;
  }
  printf("%do elemento:\n  Valor: %d\n  Endereco: %lu\n  Endereco do prox: <NULL>\n", i+1, aux, aux->valor);

  saida();
}

int menu() {
  int escolha;

  system(CLEAR);
  cout << "[1] Enqueue\n[2] Dequeue\n[3] Listar\nQual acao deseja realizar na pilha? ";
  cin >> escolha;

  return escolha;
}

int main() {
  int escolha = menu();

  while (escolha >= 1 && escolha <= 3) {
    system(CLEAR);
    switch(escolha) {
      case 1:
        int valor;

        cout << "Qual valor do elemento a ser adicionado? ";
        cin >> valor;

        enqueue(valor);
        break;
      case 2:
        dequeue();
        break;
      case 3:
        listar();
        break;
    }
    escolha = menu();
  }
  
  return 0;
}