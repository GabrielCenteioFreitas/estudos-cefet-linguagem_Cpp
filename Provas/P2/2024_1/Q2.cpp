#include <iostream>

using namespace std;

struct no {
  int info;
  struct no* esq;
  struct no* dir;
};
typedef struct no* noPtr;

void maior(noPtr p) {
  if (!p) return;
  
  if (!p->dir) {
    cout << p->info << endl;
  } else {
    maior(p->dir);
  }
}