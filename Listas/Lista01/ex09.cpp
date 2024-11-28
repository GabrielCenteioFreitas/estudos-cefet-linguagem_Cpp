#include <iostream>

using namespace std;

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

struct ctrlZ {
  int acao;
  struct ctrlZ *prox;
};
typedef struct ctrlZ* ctrlZPtr;

ctrlZPtr topo = NULL;

void saida() {
  char caractere;
  printf("\nDigite qualquer caractere para voltar ao menu ");
  cin >> caractere;
}

bool listaVazia() {
  return !topo;
}

void insert(int acao) {
  ctrlZPtr novoNo;
  novoNo = new ctrlZ;
  novoNo->acao = acao;
  novoNo->prox = topo;
  topo = novoNo;
  printf("Acao de numero %d foi adicionada ao historico!\n", acao);
  saida();
}

void remove() {
  if (listaVazia()) {
    printf("O historico esta vazio.\n");
    saida();
    return;
  }

  printf("Acao de numero %d removida!\n", topo->acao);
  topo = topo->prox;
  saida();
}

void listar() {
  if (listaVazia()) {
    printf("O historico esta vazio\n");
    saida();
    return;
  }

  ctrlZPtr aux = topo;
  int i = 0;
  do {
    printf("%do elemento:\n  Valor: %d\n  Endereco: %p\n  Endereco do prox: %p\n", i+1, aux->acao, aux, aux->prox);
    aux = aux->prox;
    i++;
  } while (aux);

  saida();
}

int menu() {
  int escolha;

  system(CLEAR);
  printf("[1] Inserir acao\n");
  printf("[2] Retirar acao\n");
  printf("[3] Listar acoes\n");
  printf("O que deseja realizar no historico? ");
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

        cout << "Qual numero da acao realizada? ";
        cin >> valor;

        insert(valor);
        break;
      case 2:
        remove();
        break;
      case 3:
        listar();
        break;
    }
    escolha = menu();
  }
  
  return 0;
}