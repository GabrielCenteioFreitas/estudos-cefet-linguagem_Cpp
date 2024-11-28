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
  return !topo;
}

void insert(int valor) {
  noPtr novoNo;
  novoNo = (noPtr) malloc (sizeof (struct no));
  novoNo->valor = valor;
  novoNo->prox = NULL;

  if (listaVazia()) {
    topo = novoNo;
    ult = novoNo;
  } else if (topo->valor >= valor) {
    novoNo->prox = topo;
    topo = novoNo;
  } else if (valor >= ult->valor) {
    ult->prox = novoNo;
    ult = novoNo;
  } else {
    noPtr aux = topo;
    while (aux->prox && aux->prox->valor < valor) {
      aux = aux->prox;
    }
    novoNo->prox = aux->prox;
    aux->prox = novoNo;
  }
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
  do {
    printf("%do elemento:\n  Valor: %d\n  Endereco: %p\n  Endereco do prox: %p\n", i+1, aux->valor, aux, aux->prox);
    aux = aux->prox;
    i++;
  } while (aux);

  saida();
}

int menu() {
  int escolha;

  system(CLEAR);
  printf("[1] Inserir\n");
  printf("[2] Listar\n");
  printf("Qual acao deseja realizar na fila? ");
  cin >> escolha;

  return escolha;
}

int main() {
  int escolha = menu();

  while (escolha >= 1 && escolha <= 2) {
    system(CLEAR);
    switch(escolha) {
      case 1:
        int valor;

        cout << "Qual valor do elemento a ser adicionado? ";
        cin >> valor;

        insert(valor);
        break;
      case 2:
        listar();
        break;
    }
    escolha = menu();
  }
  
  return 0;
}