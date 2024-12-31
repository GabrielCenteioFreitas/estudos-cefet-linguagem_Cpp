#include <iostream>

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

struct noConsumo {
  int codigo;
  struct noConsumo* prox;
};
typedef struct noConsumo* noConPtr;

struct noCliente {
  int codigo;
  struct noConsumo* topoConsumos;
  struct noCliente* prox;
  struct noCliente* ant;
};
typedef struct noCliente* noCliPtr;

bool listaVazia(void* topo) {
  return !topo;
}

void printTitle() {
  printf(BOLD);
  printf(CYAN);
  printf("---- L'art Culinaire ----\n\n");
  printf(RESET);
}

void saida() {
  char caractere;
  printf(RESET);
  printf("\nDigite qualquer caractere para voltar ao menu ");
  cin >> caractere;
}

void chegadaCliente(noCliPtr* topoEnd, noCliPtr* fimEnd) {
  int codigo = listaVazia(*topoEnd) ? 100 : (*fimEnd)->codigo + 100;
  noCliPtr novoNo = new noCliente;
  novoNo->codigo = codigo;
  novoNo->topoConsumos = NULL;
  novoNo->ant = *fimEnd;
  novoNo->prox = NULL;
  if (listaVazia(*topoEnd)) {
    *topoEnd = novoNo;
  } else {
    (*fimEnd)->prox = novoNo;
  }
  *fimEnd = novoNo;

  printf(GREEN);
  printf("Cliente de codigo %d foi adicionado com sucesso!\n", codigo);
  saida();
}

void saidaCliente(noCliPtr* topoEnd, noCliPtr* fimEnd, int codigo) {
  noCliPtr auxCli = *topoEnd;
  noConPtr auxConsumo, temp;
  int i = 0;

  if (
    codigo % 100 != 0 ||
    codigo < 100 ||
    (*fimEnd && codigo > (*fimEnd)->codigo)
  ) {
    printf(RED);
    printf("\nNenhum cliente com o codigo %d foi encontrado.\n", codigo);
    saida();
    return;
  }
  
  while (auxCli && auxCli->codigo != codigo) {
    auxCli = auxCli->prox;
  }

  if (!auxCli) {
    printf(RED);
    printf("\nNenhum cliente com o codigo %d foi encontrado.\n", codigo);
    saida();
    return;
  }

  auxConsumo = auxCli->topoConsumos;
  if (auxConsumo) printf("\nConsumos do cliente:\n");
  while (auxConsumo) {
    temp = auxConsumo;
    printf("- Produto %d\n", auxConsumo->codigo);
    auxConsumo = auxConsumo->prox;
    delete temp;
    i++;
  }

  if (auxCli->ant) auxCli->ant->prox = auxCli->prox;
  if (auxCli->prox) auxCli->prox->ant = auxCli->ant;
  if (auxCli == *topoEnd) *topoEnd = auxCli->prox;
  if (auxCli == *fimEnd) *fimEnd = auxCli->ant;

  delete auxCli;
  
  printf(GREEN);
  printf("\nCliente de codigo %d liberado!\n", codigo);
  saida();
}

void listarClientes(noCliPtr topo) {
  if (listaVazia(topo)) {
    printf(RED);
    printf("Nao ha nenhum cliente na lista.\n");
    saida();
    return;
  }

  noCliPtr aux = topo;
  noConPtr auxConsumo;
  int i = 0;
  while (aux) {
    printf("%do cliente:\n", i+1);
    printf("  Codigo: %d\n", aux->codigo);
    if (aux->topoConsumos) {
      auxConsumo = aux->topoConsumos;
      printf("  Consumos:\n");
      while (auxConsumo) {
        printf("   - Produto %d\n", auxConsumo->codigo);
        auxConsumo = auxConsumo->prox;
      }
    }
    aux = aux->prox;
    i++;
  }

  saida();
}

void consumoCliente(noCliPtr* topoEnd, noCliPtr* fimEnd, int codCliente, int codProduto) {
  noCliPtr auxCli = *topoEnd;
  noConPtr auxConsumo, novoNo = new noConsumo;

  if (
    codCliente % 100 != 0 ||
    codCliente < 100 ||
    (*fimEnd && codCliente > (*fimEnd)->codigo)
  ) {
    printf(RED);
    printf("\nNenhum cliente com o codigo %d foi encontrado.\n", codCliente);
    saida();
    return;
  }
  
  while (auxCli && auxCli->codigo != codCliente) {
    auxCli = auxCli->prox;
  }

  if (!auxCli) {
    printf(RED);
    printf("\nNenhum cliente com o codigo %d foi encontrado.\n", codCliente);
    saida();
    return;
  }

  novoNo->prox = auxCli->topoConsumos;
  novoNo->codigo = codProduto;
  auxCli->topoConsumos = novoNo;

  printf(GREEN);
  printf("\nPedido realizado com sucesso!\n");
  saida();
}

int menu() {
  int escolha;

  system(CLEAR);
  printTitle();
  cout << "[0] Sair\n"
       << "[1] Adicionar cliente\n"
       << "[2] Realizar pedido\n"
       << "[3] Liberar cliente\n"
       << "[4] Listar clientes\n\n"
       << "Qual acao deseja realizar? ";
  cin >> escolha;

  return escolha;
}

int main() {
  noCliPtr topo = NULL, fim = NULL;
  int escolha = menu(), codCliente, codProduto;

  while (escolha) {
    system(CLEAR);
    printTitle();
    switch(escolha) {
      case 1:
        chegadaCliente(&topo, &fim);
        break;
      case 2:
        cout << "Qual o codigo do cliente que realizou o pedido? ";
        cin >> codCliente;
        cout << "Qual o codigo do produto solicitado? ";
        cin >> codProduto;
        consumoCliente(&topo, &fim, codCliente, codProduto);
        break;
      case 3:
        cout << "Qual o codigo do cliente a ser liberado? ";
        cin >> codCliente;
        saidaCliente(&topo, &fim, codCliente);
        break;
      case 4:
        listarClientes(topo);
        break;
    }
    escolha = menu();
  }
  
  return 0;
}