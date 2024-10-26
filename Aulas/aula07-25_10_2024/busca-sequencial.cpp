#include <iostream>

#define T 7

using namespace std;

void sequencial (int A[], int x) {
  bool achei = false;
  int i = 0;
  while (!achei && i < T) {
    if(A[i] == x) {
      achei = true;
      cout << i+1 << "a Posicao" << endl;
    } else i++;
  }
}

int main() {
  int num, A[7]={15,30,25,12,50,10, 9};
  cout << "Numero a ser buscado: ";
  cin >> num;
  sequencial(A, num);
}