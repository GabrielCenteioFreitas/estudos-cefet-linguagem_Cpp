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
#define YELLOW "\033[33m"
#define GREY "\033[30m"

struct no {
  int info;
  struct no *esq;
  struct no *dir;
};

typedef struct no * noPtr;

bool enderecoVazio(noPtr p) {
  return !p;
}

void printarTitulo() {
  printf(BOLD);
  printf(CYAN);
  printf("---- Árvore Binária de Busca ----\n\n");
  printf(RESET);
}

void saida() {
  char caractere;
  printf(GREY);
  printf("\nDigite qualquer caractere para voltar ao menu ");
  printf(RESET);
  cin >> caractere;
}

void inserirNo(noPtr* p, int valor) {
  if (enderecoVazio(*p)) {
    *p = new no;
    (*p)->info = valor;
    (*p)->esq = NULL;
    (*p)->dir = NULL;
  } else {
    if (valor<((*p)->info))
      inserirNo(&((*p)->esq), valor);
    else
      inserirNo(&((*p)->dir), valor);
  }
}

void inserir(noPtr* endRaiz, int valor) {
  inserirNo(endRaiz, valor);

  printf(GREEN);
  printf("\nO elemento de valor %d foi adicionado!\n", valor);
  saida();
}

noPtr removerMaior(noPtr *p) {
  noPtr aux = *p;
  if (enderecoVazio(aux->dir)) {
    *p = (*p)->esq;
    return aux;
  }

  return removerMaior(&((*p)->dir));
}

bool removerNo(noPtr *p, int valor){
  noPtr aux;

  if (enderecoVazio(*p)) {
    return false;
  }

  if (valor < (*p)->info) {
    return removerNo(&((*p)->esq), valor);
  }

  if (valor > (*p)->info) {
    return removerNo(&((*p)->dir), valor);
  }

  aux = *p;
  if (enderecoVazio((*p)->esq)) {
    *p = (*p)->dir;
  } else if (enderecoVazio((*p)->dir)) {
    *p = (*p)->esq;
  } else {
    aux = removerMaior(&((*p)->esq));
    (*p)->info = aux->info;
  }
  delete aux;

  return true;
}

void remover(noPtr* endRaiz, int valor) {
  if (enderecoVazio(*endRaiz)) {
    printf(RED);
    printf("\nA árvore não possui nós.\n");
    saida();
    return;
  }

  bool retirado = removerNo(endRaiz, valor);

  if (retirado) {
    printf(GREEN);
    printf("\nO elemento de valor %d foi removido!\n", valor);
  } else {
    printf(RED);
    printf("\nO elemento de valor %d não foi encontrado.\n", valor);
  }

  saida();
}

void listarEmOrdem(noPtr p) {
  if (!enderecoVazio(p)) {
    listarEmOrdem(p->esq);
    cout << " " << p->info;
    listarEmOrdem(p->dir);
  }
}
void listarPreOrdem(noPtr p) {
  if (!enderecoVazio(p)) {
    cout << " " << p->info;
    listarPreOrdem(p->esq);
    listarPreOrdem(p->dir);
  }
}
void listarPosOrdem(noPtr p) {
  if (!enderecoVazio(p)) {
    listarPosOrdem(p->esq);
    listarPosOrdem(p->dir);
    cout << " " << p->info;
  }
}

void listar(noPtr raiz) {
  int escolha;
  system(CLEAR);
  printarTitulo();

  if (enderecoVazio(raiz)) {
    printf(RED);
    printf("A árvore não possui nós.\n");
    saida();
    return;
  }

  cout << YELLOW
       << "-- Tipos de listagem --\n"
       << RESET
       << "[1] Em ordem\n"
       << "[2] Pré ordem\n"
       << "[3] Pós ordem\n\n"
       << "Qual tipo de listagem deve ser usado? ";
  cin >> escolha;

  if (escolha < 1 || escolha > 3) return;

  system(CLEAR);
  printarTitulo();
  printf("Árvore:");
  switch(escolha) {
    case 1:
      listarEmOrdem(raiz);
      break;
    case 2:
      listarPreOrdem(raiz);
      break;
    case 3:
      listarPosOrdem(raiz);
      break;
  }
  printf("\n");
  saida();
}

noPtr buscarNo(noPtr p, int valor) {
  if (p == NULL)
    return NULL;
  if (valor == (p-> info))
    return p;
  if (valor < (p->info))
    return buscarNo((p->esq), valor);
  else
    return buscarNo((p->dir), valor);
}

void buscar(noPtr raiz, int valor) {
  if (enderecoVazio(raiz)) {
    printf(RED);
    printf("\nA árvore não possui nós.\n");
    saida();
    return;
  }

  noPtr no = buscarNo(raiz, valor);

  if (no) {
    printf(GREEN);
    printf("\nO elemento de valor %d foi encontrado no endereço ", valor);
    cout << no;
  } else {
    printf(RED);
    printf("\nO elemento de valor %d não foi encontrado!", valor);
  }

  printf("\n");
  saida();
}

int somarNos(noPtr p) {
  if (!p) return 0;

  return p->info + somarNos(p->esq) + somarNos(p->dir);
}

void somar(noPtr raiz) {
  if (enderecoVazio(raiz)) {
    printf(RED);
    printf("A árvore não possui nós.\n");
    saida();
    return;
  }

  int somatorio = somarNos(raiz);

  printf("O somatório é %d!\n", somatorio);
  saida();
}

noPtr maiorNo(noPtr p) {
  return !(p->dir) ? p : maiorNo(p->dir);
}

void maior(noPtr raiz) {
  if (enderecoVazio(raiz)) {
    printf(RED);
    printf("A árvore não possui nós.\n");
    saida();
    return;
  }

  noPtr no = maiorNo(raiz);

  printf("O maior valor é %d, correspondente ao nó de endereço ", no->info);
  cout << no;
  printf(".\n");
  saida();
}

noPtr menorNo(noPtr p) {
  return !(p->esq) ? p : menorNo(p->esq);
}

void menor(noPtr raiz) {
  if (enderecoVazio(raiz)) {
    printf(RED);
    printf("A árvore não possui nós.\n");
    saida();
    return;
  }

  noPtr no = menorNo(raiz);

  printf("O menor valor é %d, correspondente ao nó de endereço ", no->info);
  cout << no;
  printf(".\n");
  saida();
}

int contarNosDeGrauUm(noPtr p) {
  if (!p) return 0;

  if (
    (!p->esq && p->dir) ||
    (!p->dir && p->esq)
  ) {
    return 1 + contarNosDeGrauUm(p->esq) + contarNosDeGrauUm(p->dir);
  }

  return contarNosDeGrauUm(p->esq) + contarNosDeGrauUm(p->dir);
}

void nosDeGrauUm(noPtr raiz) {
  if (enderecoVazio(raiz)) {
    printf(RED);
    printf("A árvore não possui nós.\n");
    saida();
    return;
  }

  int qntNosGrauUm = contarNosDeGrauUm(raiz);

  printf("A árvore tem %d nó(s) de grau 1!\n", qntNosGrauUm);
  saida();
}

void contarNos(noPtr p, int *qnt) {
  if (enderecoVazio(p)) return;

  (*qnt)++;
  contarNos(p->dir, qnt);
  contarNos(p->esq, qnt);
}

void nos(noPtr raiz) {
  if (enderecoVazio(raiz)) {
    printf(RED);
    printf("A árvore não possui nós.\n");
    saida();
    return;
  }

  int qntNos = 0;
  contarNos(raiz, &qntNos);

  printf("A árvore tem %d nó(s)!\n", qntNos);
  saida();
}

int menu() {
  int escolha;

  system(CLEAR);
  printarTitulo();
  cout << "[1] Inserir\n"
       << "[2] Remover\n"
       << "[3] Listar\n"
       << "[4] Buscar\n"
       << "[5] Ver somatório\n"
       << "[6] Ver nó de maior valor\n"
       << "[7] Ver nó de menor valor\n"
       << "[8] Ver quantidade de nós\n"
       << "[9] Ver quantidade de nós com grau 1\n"
       << "\nQual acao deseja realizar? ";
  cin >> escolha;

  return escolha;
}

int main() {
  noPtr raiz = NULL;
  int escolha = menu(), valor;

  while (escolha) {
    system(CLEAR);
    printarTitulo();
    switch(escolha) {
      case 1:
        cout << "Qual valor do nó a ser adicionado? ";
        cin >> valor;

        inserir(&raiz, valor);
        break;
      case 2:
        cout << "Qual valor do nó a ser removido? ";
        cin >> valor;

        remover(&raiz, valor);
        break;
      case 3:
        listar(raiz);
        break;
      case 4:
        cout << "Qual valor do nó a ser procurado? ";
        cin >> valor;

        buscar(raiz, valor);
        break;
      case 5:
        somar(raiz);
        break;
      case 6:
        maior(raiz);
        break;
      case 7:
        menor(raiz);
        break;
      case 8:
        nos(raiz);
        break;
      case 9:
        nosDeGrauUm(raiz);
        break;
    }
    escolha = menu();
  }
  
  return 0;
}