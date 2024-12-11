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
};
typedef struct no* noPtr;

bool listaVazia(noPtr finalEnd) {
  return !finalEnd;
}

void saida() {
  char caractere;
  printf("\nDigite qualquer caractere para voltar ao menu ");
  cin >> caractere;
}

void inserir(noPtr* finalEnd, int* qtdEnd, int valor) {
  noPtr novoNo = new no;
  novoNo->info = valor;

  if (!listaVazia(*finalEnd)) {
    novoNo->prox = (*finalEnd)->prox;
    (*finalEnd)->prox = novoNo;
  } else {
    novoNo->prox = novoNo;
  }

  *finalEnd = novoNo;

  (*qtdEnd)++;
  printf("Elemento de valor %d foi adicionado!\n", valor);
  saida();
}

void retirar(noPtr* finalEnd, int* qtdEnd) {
  if (listaVazia(*finalEnd)) {
    printf("A lista nao possui nenhum elemento.\n");
    saida();
    return;
  }

  noPtr temp = (*finalEnd)->prox;
  (*finalEnd)->prox = (*finalEnd)->prox->prox;
  delete temp;

  (*qtdEnd)--;
  printf("Elemento removido!\n");
  saida();
}

void listar(noPtr final, int qtd) {
  if (listaVazia(final)) {
    printf("A lista esta vazia\n");
    saida();
    return;
  }

  noPtr aux = final->prox;
  for (int i = 0; i < qtd; i++) {
    cout << i+1 << "o elemento:\n"
         <<"  Valor: " << aux->info << endl
         <<"  Endereco: " << aux << endl
         <<"  Endereco do prox: " << aux->prox << endl;
    aux = aux->prox;
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
  noPtr final = NULL;
  int escolha = menu(), qtd = 0;

  while (escolha >= 1 && escolha <= 3) {
    system(CLEAR);
    switch(escolha) {
      case 1:
        int valor;

        cout << "Qual valor do elemento a ser adicionado? ";
        cin >> valor;

        inserir(&final, &qtd, valor);
        break;
      case 2:
        retirar(&final, &qtd);
        break;
      case 3:
        listar(final, qtd);
        break;
    }
    escolha = menu();
  }
  
  return 0;
}