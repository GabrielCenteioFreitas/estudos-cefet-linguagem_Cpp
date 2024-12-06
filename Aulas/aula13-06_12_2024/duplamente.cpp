#include <iostream>

using namespace std;

#ifdef _WIN32
  #define CLEAR "cls"
#else
  #define CLEAR "clear"
#endif

struct no {
  int info;
  struct no* prox;
  struct no* ant;
};
typedef struct no* noPtr;

noPtr topo = NULL;

bool listaVazia() {
  return !topo;
}

void saida() {
  char caractere;
  printf("\nDigite qualquer caractere para voltar ao menu ");
  cin >> caractere;
}

void inserir(int valor) {
  noPtr novoNo = new no;
  novoNo->info = valor;
  novoNo->ant = NULL;
  if (listaVazia()) {
    novoNo->prox = NULL;
  } else {
    novoNo->prox = topo;
    topo->ant = novoNo;
  }
  topo = novoNo;

  printf("Elemento de valor %d foi adicionado ao topo!\n", valor);
  saida();
}

void retirar() {
  if (listaVazia()) return;

  noPtr temp = topo;
  if (!topo->prox) {
    topo = NULL;
  } else {
    topo = topo->prox;
    topo->ant = NULL;
  }
  delete temp;

  printf("Elemento do topo removido!\n");
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
  while (aux) {
    cout << i+1 << "o elemento:\n"
         <<"  Valor: " << aux->info << endl
         <<"  Endereco: " << aux << endl
         <<"  Endereco do prox: " << aux->prox << endl
         <<"  Endereco do ant: " << aux->ant << endl;
    aux = aux->prox;
    i++;
  }

  saida();
}

int menu() {
  int escolha;

  system(CLEAR);
  cout << "[1] Inserir\n"
       << "[2] Retirar\n"
       << "[3] Listar\n"
       << "Qual acao deseja realizar? ";
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

        inserir(valor);
        break;
      case 2:
        retirar();
        break;
      case 3:
        listar();
        break;
    }
    escolha = menu();
  }
  
  return 0;
}