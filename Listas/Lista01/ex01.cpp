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
  noPtr novoNo;
  novoNo = (noPtr) malloc (sizeof (struct no));
  novoNo->valor = valor;
  novoNo->prox = topo;
  topo = novoNo;
  printf("Elemento de valor %d foi adicionado ao topo da pilha!\n", valor);
  saida();
}

void pop() {
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
  do {
    printf("%do elemento:\n  Valor: %d\n  Endereco: %p\n  Endereco do prox: %p\n", i+1, aux->valor, aux, aux->prox);
    aux = aux->prox;
    i++;
  } while (aux);

  saida();
}

void contar() {
  if (listaVazia()) {
    printf("A lista nao tem nenhum elemento.\n");
    saida();
    return;
  }

  int i = 0;
  for (noPtr aux = topo; aux; i++, aux = aux->prox);
  printf("A lista tem %d elemento%s.\n", i, i == 1 ? "" : "s");

  saida();
}

int menu() {
  int escolha;

  system(CLEAR);
  printf("[1] Empilhar\n");
  printf("[2] Desempilhar\n");
  printf("[3] Listar\n");
  printf("[4] Contar\n");
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
        listar();
        break;
      case 4:
        contar();
        break;
    }
    escolha = menu();
  }
  
  return 0;
}