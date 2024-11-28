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

void saida() {
  char caractere;
  printf("\nDigite qualquer caractere para voltar ao menu ");
  cin >> caractere;
}

bool listaVazia() {
  return !topo;
}

void push(int valor) {
  noPtr novoNo = new no;
  novoNo->valor = valor;
  novoNo->prox = topo;
  topo = novoNo;

  saida();
}

void pop() {
  if (listaVazia()) {
    printf("A lista esta vazia\n");
    saida();
    return;
  }

  noPtr temp = topo;
  topo = topo->prox;
  delete temp;

  saida();
}

void listar() {
  if (listaVazia()) {
    printf("A lista esta vazia\n");
    saida();
    return;
  }

  int i = 0;
  for (noPtr aux = topo; aux; i++, aux = aux->prox) {
    printf("%do elemento:\n", i+1);
    printf("  Valor: %d\n", aux->valor);
    printf("  Endereco: %p\n", aux);
    printf("  Endereco do prox: %p\n", aux->prox);
  }

  saida();
}

void retirar(int valor) {
  if (listaVazia()) return;

  if (topo->valor == valor) {
    noPtr temp = topo;
    topo = topo->prox;
    delete temp;
    return;
  }

  noPtr ant = topo, aux = topo ? topo->prox : NULL;
  while (aux) {
    if (aux->valor == valor) {
      ant->prox = aux->prox;
      delete aux;
      aux = ant->prox;
      break;
    }

    ant = aux;
    aux = aux->prox;
  }
}

void trocarMaior() {
  if (listaVazia()) {
    printf("A lista esta vazia\n");
    saida();
    return;
  }

  if (!topo->prox) {
    printf("O numero de maior valor foi movido para a 1a posicao!\n");
    saida();
    return;
  }

  int maiorValor = topo->valor;
  noPtr aux = topo;
  while (aux) {
    if (aux->valor > maiorValor) {
      maiorValor = aux->valor;
    }

    aux = aux->prox;
  }

  retirar(maiorValor);
  noPtr novoNo = new no;
  novoNo->valor = maiorValor;
  novoNo->prox = topo;
  topo = novoNo;

  printf("O numero de maior valor foi movido para a 1a posicao!\n");
  saida();
}

int menu() {
  int escolha;

  system(CLEAR);
  printf("[1] Empilhar\n");
  printf("[2] Desempilhar\n");
  printf("[3] Trocar maior\n");
  printf("[4] Listar\n");
  printf("Qual acao deseja realizar na pilha? ");
  cin >> escolha;

  return escolha;
}

int main() {
  int escolha = menu();

  while (escolha >= 1 && escolha <= 4) {
    system(CLEAR);
    switch(escolha) {
      case 1:
        int valor;

        cout << "Qual valor do elemento a ser adicionado? ";
        cin >> valor;

        push(valor);
        break;
      case 2:
        pop();
        break;
      case 3:
        trocarMaior();
        break;
      case 4:
        listar();
        break;
    }
    escolha = menu();
  }
  
  return 0;
}