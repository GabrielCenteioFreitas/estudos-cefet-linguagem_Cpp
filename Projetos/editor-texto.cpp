#include <iostream>
#include <string>

using namespace std;

#ifdef _WIN32
  #define CLEAR "cls"
#else
  #define CLEAR "clear"
#endif

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define CYAN "\033[36m"

struct no {
  string conteudo;
  struct no* prox;
  struct no* ant;
};
typedef struct no* noPtr;

bool listaVazia(noPtr topo) {
  return !topo;
}

void printTitle() {
  printf(BOLD);
  printf(CYAN);
  printf("---- Editor de texto ----\n\n");
  printf(RESET);
}

void saida() {
  char caractere;
  printf(RESET);
  printf("\nDigite qualquer caractere para voltar ao menu ");
  cin >> caractere;
}

void inserir(noPtr* topoEnd, noPtr* fimEnd, string conteudo) {
  noPtr novoNo = new no;
  novoNo->conteudo = conteudo;
  novoNo->ant = *fimEnd;
  novoNo->prox = NULL;
  if (listaVazia(*topoEnd)) {
    *topoEnd = novoNo;
  } else {
    (*fimEnd)->prox = novoNo;
  }
  *fimEnd = novoNo;

  printf(GREEN);
  printf("\nLinha inserida com sucesso!\n");
  saida();
}

void excluir(noPtr* topoEnd, noPtr* fimEnd, int numLinha) {
  noPtr aux = *topoEnd;

  if (!(*topoEnd)) {
    printf(RED);
    printf("\nO texto nao possui nenhum conteudo.\n");
    saida();
    return;
  }

  if (numLinha <= 0) {
    printf(RED);
    printf("\nInsira um valor maior que 0.\n");
    saida();
    return;
  }

  int i = 0;
  for (i = 0; i < numLinha && aux; i++) {
    aux = aux->prox;
  }
  
  if (!aux) {
    printf(RED);
    printf("O texto possui apenas %d linha(s).\n", i);
    saida();
    return;
  }

  if (aux->ant) aux->ant->prox = aux->prox;
  if (aux->prox) aux->prox->ant = aux->ant;
  if (aux == *topoEnd) *topoEnd = aux->prox;
  if (aux == *fimEnd) *fimEnd = aux->ant;

  printf(GREEN);
  cout << "\nLinha de conteudo \"" << aux->conteudo << "\" foi excluida!\n";
  delete aux;
  saida();
}

void listar(noPtr topoOuFim, bool mostrarInvertido) {
  noPtr aux = topoOuFim;

  if (listaVazia(topoOuFim)) {
    printf(RED);
    printf("O texto nao possui conteudo.\n");
    saida();
    return;
  }

  while (aux) {
    cout << aux->conteudo << endl;
    aux = mostrarInvertido ? aux->ant : aux->prox;
  }

  saida();
}

void mover(noPtr* topoEnd, noPtr* fimEnd, int numLinha1, int numLinha2) {
  noPtr aux1 = *topoEnd, aux2 = *topoEnd, novoNo = new no, temp;

  if (!(*topoEnd)) {
    printf(RED);
    printf("\nO texto nao possui nenhum conteudo.\n");
    saida();
    return;
  }

  if (numLinha1 < 0 || numLinha2 < 0) {
    printf(RED);
    printf("\nInsira valores maiores que 0.\n");
    saida();
    return;
  }

  if (numLinha1 == numLinha2) {
    printf(RED);
    printf("\nInsira valores diferentes.\n");
    saida();
    return;
  }

  int i = 0;
  for (i = 0; i < numLinha1 && aux1; i++) {
    aux1 = aux1->prox;
  }
  
  if (!aux1) {
    printf(RED);
    printf("\nO texto possui apenas %d linha(s).\n", i);
    saida();
    return;
  }

  for (int j = 0; j < numLinha2 && aux2; j++) {
    aux2 = aux2->prox;
  }
  
  novoNo->conteudo = aux1->conteudo;
  if (!aux2 || aux2 == *fimEnd) {
    novoNo->ant = *fimEnd;
    novoNo->prox = NULL;
    (*fimEnd)->prox = novoNo;
    *fimEnd = novoNo;
  } else if (aux2 == *topoEnd) {
    novoNo->ant = NULL;
    novoNo->prox = *topoEnd;
    (*topoEnd)->ant = novoNo;
    *topoEnd = novoNo;
  } else if (numLinha1 < numLinha2) {
    novoNo->ant = aux2;
    novoNo->prox = aux2->prox;
    if (aux2->prox) aux2->prox->ant = novoNo;
    aux2->prox = novoNo;
  } else {
    novoNo->ant = aux2->ant;
    novoNo->prox = aux2;
    if (aux2->ant) aux2->ant->prox = novoNo;
    aux2->ant = novoNo;
  }

  temp = aux1;
  if (temp->ant) temp->ant->prox = temp->prox;
  if (temp->prox) temp->prox->ant = temp->ant;
  if (temp == *fimEnd) *fimEnd = (*topoEnd)->ant;
  if (temp == *topoEnd) *topoEnd = (*topoEnd)->prox;
  delete temp;

  printf(GREEN);
  printf("\nLinhas movidas com sucesso!\n");
  saida();
}

int menu() {
  int escolha;

  system(CLEAR);
  printTitle();
  cout << "[0] Sair\n"
       << "[1] Inserir linha\n"
       << "[2] Excluir linha\n"
       << "[3] Mostrar texto\n"
       << "[4] Mostrar texto invertido\n"
       << "[5] Mover linhas\n\n"
       << "Qual acao deseja realizar? ";
  cin >> escolha;

  return escolha;
}

int main() {
  noPtr topo = NULL, fim = NULL;
  int escolha = menu(), numLinha1, numLinha2;
  string conteudo;

  while (escolha) {
    system(CLEAR);
    printTitle();
    switch(escolha) {
      case 1:
        cout << "Digite o conteudo da nova linha: ";
        cin.ignore();
        getline(cin, conteudo);
        inserir(&topo, &fim, conteudo);
        break;
      case 2:
        cout << "Qual o numero da linha a ser excluida? ";
        cin >> numLinha1;
        excluir(&topo, &fim, numLinha1-1);
        break;
      case 3:
        listar(topo, false);
        break;
      case 4:
        listar(fim, true);
        break;
      case 5:
        cout << "Qual o numero da linha a ser movida? ";
        cin >> numLinha1;
        cout << "Qual o numero da linha onde o trecho sera colocado? ";
        cin >> numLinha2;
        mover(&topo, &fim, numLinha1-1, numLinha2-1);
        break;
    }
    escolha = menu();
  }
  
  return 0;
}