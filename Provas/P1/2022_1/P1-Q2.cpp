#include <iostream>

using namespace std;

struct endereco {
  int num;
  struct endereco* prox;
};
typedef struct endereco* enderecoPtr;

enderecoPtr topo = NULL;

void adicionarEnderecoDeRetorno() {
	enderecoPtr novoEndereco = new endereco;
	cout << "Digite o numero do endereco: ";
	cin >> novoEndereco->num;
	novoEndereco->prox = topo;
	topo = novoEndereco;
}

void retirarEndereco() {
	enderecoPtr temp = topo;
	if (topo) {
		topo = topo->prox;
		delete(temp);
		cout << "\nO endereco foi retirado da pilha." << endl;
	} else cout << "\nLista vazia!" << endl;
}