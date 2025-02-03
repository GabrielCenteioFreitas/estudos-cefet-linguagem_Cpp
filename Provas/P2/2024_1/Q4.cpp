#include <iostream>

using namespace std;

struct no {
  int info;
  struct no* prox;
};
typedef struct no* noPtr;

int main() {
  noPtr raiz;

  // lista é preenchida...

  int num;
  cin >> num;

  noPtr aux = raiz;
  for (int i = 0; i < 87; i++)   {
    aux = aux->prox;
  }
  cout << aux->info;
}