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
    if (valor >= (*finalEnd)->prox->info) {
      novoNo->prox = (*finalEnd)->prox;
      novoNo->ant = (*finalEnd);
      (*finalEnd)->prox->ant = novoNo;
      (*finalEnd)->prox = novoNo;
    } else if (valor <= (*finalEnd)->info) {
      novoNo->prox = (*finalEnd)->prox;
      novoNo->ant = (*finalEnd);
      (*finalEnd)->prox->ant = novoNo;
      (*finalEnd)->prox = novoNo;
      *finalEnd = novoNo;
    } else {
      noPtr aux = (*finalEnd)->prox;
      for (int i = 0; i < (*qtdEnd); i++) {
        if (valor >= aux->prox->info) {
          aux->prox->ant = novoNo;
          novoNo->prox = aux->prox;
          aux->prox = novoNo;
          novoNo->ant = aux;
          break;
        }
        aux = aux->prox;
      }
    }
  } else {
    novoNo->prox = novoNo;
    novoNo->ant = novoNo;
    *finalEnd = novoNo;
  }

  (*qtdEnd)++;
  printf("Elemento de valor %d foi adicionado!\n", valor);
  saida();
}

void retirar(noPtr* finalEnd, int* qtdEnd, int valor) {
  if (listaVazia(*finalEnd)) {
    printf("A lista nao possui nenhum elemento.\n");
    saida();
    return;
  }

  if (valor < (*finalEnd)->info || valor > (*finalEnd)->prox->info) {
    printf("Esse numero nao esta na lista.\n");
    saida();
    return;
  }

  noPtr temp;
  bool numeroEstaNaLista = false;
  if (valor == (*finalEnd)->prox->info) {
    numeroEstaNaLista = true;
    if (*qtdEnd > 1) {
      temp = (*finalEnd)->prox;
      (*finalEnd)->prox->prox->ant = (*finalEnd);
      (*finalEnd)->prox = (*finalEnd)->prox->prox;
      delete temp;
    } else {
      *finalEnd = NULL;
    }
  } else if (valor == (*finalEnd)->info) {
    numeroEstaNaLista = true;
    temp = *finalEnd;
    (*finalEnd)->prox->ant = (*finalEnd)->ant;
    (*finalEnd)->ant->prox = (*finalEnd)->prox;
    *finalEnd = (*finalEnd)->ant;
    delete temp;
  } else {
    temp = (*finalEnd)->prox;
    for (int i = 0; i < (*qtdEnd); i++) {
      if (valor == temp->info) {
        temp->ant->prox = temp->prox;
        temp->prox->ant = temp->ant;
        numeroEstaNaLista = true;
        break;
      }
      temp = temp->prox;
    }
    if (numeroEstaNaLista)
      delete temp;
  }

  if (numeroEstaNaLista) {
    (*qtdEnd)--;
    printf("Elemento removido!\n");
  } else {
    printf("Esse numero nao esta na lista.\n");
  }
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
         <<"  Endereco do prox: " << aux->prox << endl
         <<"  Endereco do ant: " << aux->ant << endl;
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
  int valor;

  while (escolha >= 1 && escolha <= 3) {
    system(CLEAR);
    switch(escolha) {
      case 1:
        cout << "Qual valor do elemento a ser adicionado? ";
        cin >> valor;

        inserir(&final, &qtd, valor);
        break;
      case 2:
        cout << "Qual valor do elemento a ser retirado? ";
        cin >> valor;

        retirar(&final, &qtd, valor);
        break;
      case 3:
        listar(final, qtd);
        break;
    }
    escolha = menu();
  }
  
  return 0;
}