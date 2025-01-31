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
  int info, altDir, altEsq;
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
  printf("---- Árvore AVL ----\n\n");
  printf(RESET);
}

void saida() {
  char caractere;
  printf(GREY);
  printf("\nDigite qualquer caractere para voltar ao menu ");
  printf(RESET);
  cin >> caractere;
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

void acharNoEPai(noPtr** pai, noPtr** no, int valor) {
  while (**pai) {
    if ((**pai)->dir && (**pai)->dir->info == valor) {
      *no = &(**pai)->dir;
      break;
    }

    if ((**pai)->esq && (**pai)->esq->info == valor) {
      *no = &(**pai)->esq;
      break;
    }

    if (valor < (**pai)->info) {
      *pai = &(**pai)->esq;
    } else if (valor > (**pai)->info) {
      *pai = &(**pai)->dir;
    } else {
      *no = *pai;
      *pai = NULL;
      break;
    }
  }
}

void atualizarAlturaPai(noPtr* pai, noPtr* no) {
  int novaAltPai;

  if (!pai) return;

  novaAltPai = (*no)->altEsq > (*no)->altDir
    ? (*no)->altEsq + 1
    : (*no)->altDir + 1;
  if ((*pai)->dir == *no) {
    (*pai)->altDir = novaAltPai;
  } else {
    (*pai)->altEsq = novaAltPai;
  }
}

void rotacaoAEsquerda(noPtr* endRaiz, int valor) {
  noPtr *pai = endRaiz, *no = NULL;

  acharNoEPai(&pai, &no, valor);

  if (!no) return;

  noPtr noAnt = *no;
  *no = (*no)->dir;
  noAnt->dir = (*no)->esq;
  noAnt->altDir = (*no)->altEsq;
  (*no)->esq = noAnt;
  (*no)->altEsq = noAnt->altEsq > noAnt->altDir
    ? noAnt->altEsq + 1
    : noAnt->altDir + 1;
  if (pai) atualizarAlturaPai(pai, no);
}

void rotacaoADireita(noPtr* endRaiz, int valor) {
  noPtr *pai = endRaiz, *no = NULL;

  acharNoEPai(&pai, &no, valor);

  if (!no) return;

  noPtr noAnt = *no;
  *no = (*no)->esq;
  noAnt->esq = (*no)->dir;
  noAnt->altEsq = (*no)->altDir;
  (*no)->dir = noAnt;
  (*no)->altDir = noAnt->altDir > noAnt->altEsq
    ? noAnt->altDir + 1
    : noAnt->altEsq + 1;
  if (pai) atualizarAlturaPai(pai, no);
}

void balancear(noPtr* endRaiz, noPtr p) {
  int fb, fbFilho;

  if (!p) return;

  balancear(endRaiz, p->esq);
  balancear(endRaiz, p->dir);
  
  p->altEsq = p->esq
    ? p->esq->altEsq > p->esq->altDir
        ? p->esq->altEsq + 1
        : p->esq->altDir + 1
    : 0;
  p->altDir = p->dir
    ? p->dir->altEsq > p->dir->altDir
        ? p->dir->altEsq + 1
        : p->dir->altDir + 1
    : 0;

  fb = p->altEsq - p->altDir;

  if (fb > 1) {
    fbFilho = p->esq->altEsq - p->esq->altDir;
    if (fbFilho >= 0) {
      rotacaoADireita(endRaiz, p->info);
    } else {
      rotacaoAEsquerda(endRaiz, p->esq->info);
      rotacaoADireita(endRaiz, p->info);
    }
  } else if (fb < -1) {
    fbFilho = p->dir->altEsq - p->dir->altDir;
    if (fbFilho <= 0) {
      rotacaoAEsquerda(endRaiz, p->info);
    } else {
      rotacaoADireita(endRaiz, p->dir->info);
      rotacaoAEsquerda(endRaiz, p->info);
    }
  }
}

bool inserirNo(noPtr* p, int valor) {
  if (enderecoVazio(*p)) {
    *p = new no;
    (*p)->info = valor;
    (*p)->esq = NULL;
    (*p)->dir = NULL;
    (*p)->altDir = 0;
    (*p)->altEsq = 0;
    return true;
  } else {
    if (valor < ((*p)->info)) {
      if (inserirNo(&((*p)->esq), valor)) {
        (*p)->altEsq++;
        return ((*p)->altEsq > (*p)->altDir);
      }
    } else if (
      inserirNo(&((*p)->dir), valor)
    ) {
      (*p)->altDir++;
      return ((*p)->altDir > (*p)->altEsq);
    }
  }
  return false;
}

void inserir(noPtr* endRaiz, int valor) {
  inserirNo(endRaiz, valor);
  balancear(endRaiz, *endRaiz);

  printf(GREEN);
  printf("\nO elemento de valor %d foi adicionado!\n", valor);
  saida();
}

noPtr removerMaior(noPtr *p) {
  noPtr* filhoDir = &((*p)->dir), aux;

  if (enderecoVazio(*filhoDir)) {
    aux = *p;
    *p = (*p)->esq;
    return aux;
  }

  if (enderecoVazio((*filhoDir)->dir)) {
    aux = *filhoDir;
    *filhoDir = (*filhoDir)->esq;
    (*p)->altDir--;
    return aux;
  }

  return removerMaior(filhoDir);
}

bool removerNo(noPtr *p, int valor){
  noPtr aux;

  if (enderecoVazio(*p)) {
    return false;
  }

  if (valor < (*p)->info && removerNo(&((*p)->esq), valor)) {
    (*p)->altEsq--;
    return enderecoVazio((*p)->dir);
  }

  if (valor > (*p)->info && removerNo(&((*p)->dir), valor)) {
    (*p)->altDir--;
    return enderecoVazio((*p)->esq);
  }

  aux = *p;
  if (enderecoVazio((*p)->esq)) {
    *p = (*p)->dir;
  } else if (enderecoVazio((*p)->dir)) {
    *p = (*p)->esq;
  } else {
    aux = removerMaior(&((*p)->esq));
    (*p)->info = aux->info;
    if ((*p)->esq)
      (*p)->altEsq = (*p)->esq->altEsq + 1;
    else
      (*p)->altEsq = 0;
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

  noPtr no = buscarNo(*endRaiz, valor);

  if (!no) {
    printf(RED);
    printf("\nO elemento de valor %d não foi encontrado.\n", valor);
    saida();
    return;
  }

  removerNo(endRaiz, valor);
  balancear(endRaiz, *endRaiz);

  printf(GREEN);
  printf("\nO elemento de valor %d foi removido!\n", valor);

  saida();
}

void listarEmOrdem(noPtr p) {
  if (!enderecoVazio(p)) {
    listarEmOrdem(p->esq);
    cout <<"Nó de valor " << p->info << ":\n"
         <<"  Altura Esquerda: " << p->altEsq << endl
         <<"  Altura Direita: " << p->altDir << endl;
    listarEmOrdem(p->dir);
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

  system(CLEAR);
  printarTitulo();
  listarEmOrdem(raiz);
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
        cout << "Qual valor do nó a ser girado pra esquerda? ";
        cin >> valor;

        rotacaoAEsquerda(&raiz, valor);
        break;
      case 6:
        cout << "Qual valor do nó a ser girado pra direita? ";
        cin >> valor;

        rotacaoADireita(&raiz, valor);
        break;
    }
    escolha = menu();
  }
  
  return 0;
}