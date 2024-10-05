#include <iostream>
#include <iomanip>

using namespace std;

#define qtd_funcs 15

void sort(float array[], int tamanho) {
  for (int i = 0; i < tamanho-1; i++) {
    for (int j = i+1; j < tamanho; j++) {
      if (array[i] < array[j]) {
        int aux = array[i];
        array[i] = array[j];
        array[j] = aux;
      }
    }
  }
}

int main() {
  string matriculas[qtd_funcs];
  float salarios[qtd_funcs];

  for (int i = 0; i < qtd_funcs; i++) {
    cout << "Matricula do " << i+1 << "o funcionario: ";
    cin >> matriculas[i];
    cout << "Salario do " << i+1 << "o funcionario: ";
    cin >> salarios[i];
  }

  // Letra A
  float salariosOrdenados[qtd_funcs];
  for (int i = 0; i < qtd_funcs; i++) {
    salariosOrdenados[i] = salarios[i];
  }
  sort(salariosOrdenados, qtd_funcs);
  cout << "\nSalários em ordem decrescente: ";
  for (int i = 0; i < qtd_funcs; i++) {
    cout << "R$ " << fixed << setprecision(2) << salariosOrdenados[i];
    if (i != qtd_funcs-1) {
      cout << ", ";
    }
  }
  cout << "\n\n";

  // Letra B
  float soma = 0;
  for (int i = 0; i < qtd_funcs; i++) {
    soma += salarios[i];
  }
  cout << "A soma dos salários é: R$ " << fixed << setprecision(2) << soma << "\n";

  // Letra C
  float media = soma / qtd_funcs;
  int qtdMenoresSalarios = 0;
  cout << "\nSalários menores que a média: \n";
  for (int i = 0; i < qtd_funcs; i++) {
    if (salarios[i] < media) {
      cout << "Matrícula: " << matriculas[i] << " - Salário: R$ " << fixed << setprecision(2) << salarios[i] << "\n";
      qtdMenoresSalarios++;
    }
  }
  cout << "Quantidade: " << qtdMenoresSalarios << "\n";

  return 0;
}