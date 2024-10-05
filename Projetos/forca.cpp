#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

string palavra_aleatoria;
int tamanho, erros = 0;
string letras_acertadas;
char letras_erradas[6] = {""};

char toLowerCase(char letra) {
  if (letra >= 65 && letra <= 90) {
    return letra + 32;
  }

  return letra;
}

char toUpperCase(char letra) {
  if (letra >= 97 && letra <= 122) {
    return letra - 32;
  }

  return letra;
}

bool isLetterInArray(char letter, char array[], int length) {
  for (int i = 0; i < length; i++) {
    if (letter == array[i]) {
      return true;
    }
  }

  return false;
}

bool verificarVitoria() {
  for (int i = 0; i < tamanho; i++) {
    if (letras_acertadas[i] == '_') {
      return false;
    }
  }

  return true;
}

string sortearPalavra() {
  string palavras[] = {"casa", "arvore", "carro", "bola", "gato", "cachorro", "livro", "mesa", "caneta", "chuva", "sol", "mar", "vento", "praia", "montanha", "rio", "telefone", "computador", "papel", "copo", "porta", "janela", "cadeira", "corrente", "lampada", "chave", "chuva", "sapato", "estrada", "pedra", "terra", "folha", "flor", "maquina", "fruta", "panela", "lapis", "borracha", "escola", "pessoa", "pote", "garfo", "faca", "prato", "tigela", "garrafa", "fogo", "terra", "arvore", "terra", "fogo", "pedra", "rio", "lago", "ponte", "piscina", "pneu", "cama", "cobertor", "travesseiro", "almofada", "armario", "espelho", "brinquedo", "dinheiro", "banco", "caixa", "cofre", "telefone", "celular", "tablet", "escova", "espuma", "escada", "sabonete", "toalha", "cabelo", "unha", "mao", "barriga", "braco", "perna", "cabeca", "orelha", "nariz", "boca", "vermelho", "verde", "azul", "amarelo", "rosa", "laranja", "roxo", "marrom", "preto", "branco", "cinza", "teclado", "lasanha", "pizza", "carne", "vaca", "galinha", "porco", "banana", "maca", "pessego", "comida", "alimento", "morte", "vida", "felicidade", "tristeza", "amor", "programar", "sorte", "aleatorio", "monitor", "tela", "palavra", "termo", "jogo", "bicicleta", "aviao", "chocolate", "relogio", "casaco", "piano", "cachecol", "radio", "musica", "feliz", "triste", "calor", "lua", "estrela", "futebol", "basquete", "volei", "nadar", "dancar", "dormir", "acordar", "correr", "andar", "divertido", "brincar", "trabalhar", "trabalho", "amigo", "amiga", "bolo", "suco", "pao", "leite", "cha", "biscoito", "macarrao", "sorvete", "doce", "salgado", "odio", "alegria", "medo", "saudade", "esperanca", "paz", "guerra", "amizade", "inimigo", "familia", "companheiro", "companheira", "irmao", "irma", "pai", "mae", "primo", "prima", "avo", "tio", "tia", "filho", "filha", "neto", "neta", "genro", "nora", "padrinho", "madrinha", "vizinho", "vizinha", "colega", "professor", "professora", "aluno", "aluna", "medico", "engenheiro", "advogado", "programador", "artista", "musico", "escritor", "pintor", "chef", "jardineiro", "padeiro", "policial", "bombeiro", "vendedor", "garcom", "motorista", "piloto", "macaco", "girafa", "elefante", "leao", "tigre", "urso", "passaro", "peixe", "tubarao", "tartaruga", "polvo", "camera", "veleiro", "abacaxi", "tenis", "brinco", "caneca", "grande", "pequeno", "alto", "baixo", "gordo", "magro", "cabeludo", "careca", "velho", "novo", "jovem", "idoso", "feio", "bonito", "simpatico", "antipatico", "educado", "generoso", "egoista", "corajoso", "medroso", "otimista", "pessimista", "curioso", "preocupado", "criativo", "racional", "alegre", "energico", "preguicoso", "paciente", "impaciente", "calmo", "agitado", "organizado", "baguncado",  "silencioso", "barulhento", "lento", "rapido", "delicado", "rude", "azedo", "picante", "amargo", "macio", "aspero", "quente", "frio", "claro", "escuro", "ensolarado", "nublado", "chuvoso", "gelado", "umido", "seco", "limpo", "sujo", "cheio", "vazio", "aberto", "fechado", "longe", "perto", "caro", "barato", "positivo", "negativo"};
  int tamanho = sizeof(palavras) / sizeof(palavras[0]);

  int numero_sorteado = rand() % tamanho;

  return palavras[numero_sorteado];
}

char pedirLetra() {
  char letra;

  cout << "\n\n";
  cout << "Insira uma letra: ";
  cin >> letra;

  return letra;
}

void verificarLetraNaPalavra(char letra) {
  int acertou = 0;

  for (int i = 0; i < tamanho; i++) {
    if (letra == palavra_aleatoria[i]) {
      letras_acertadas[i] = letra;
      acertou++;
    }
  }

  if (!acertou && !isLetterInArray(letra, letras_erradas, 6)) {
    letras_erradas[erros] = letra;
    erros++;
  }
}

void printarBoneco() {
  char letras_erradas_string[13] = "";
  for (int i = 0; i < 12; i++) {
    if (i%2 == 0) {
      letras_erradas_string[i] = toUpperCase(letras_erradas[i/2]);
    } else {
      letras_erradas_string[i] = ' ';
    }
  }

  printf(">>>>>>> Jogo da Forca <<<<<<<\n\n");

  switch(erros) {
    case 0:
      printf(" ______\n |    |        %s\n |\n |\n |\n |\n |             ", letras_erradas_string);
      break;
    case 1:
      printf(" ______\n |    |        %s\n |    O\n |\n |\n |\n |             ", letras_erradas_string);  
      break;
    case 2:
      printf(" ______\n |    |        %s\n |    O\n |    |\n |    |\n |\n |             ", letras_erradas_string); 
      break;
    case 3:
      printf(" ______\n |    |        %s\n |    O\n |   /|\n |    |\n |\n |             ", letras_erradas_string);
      break;
    case 4:
      printf(" ______\n |    |        %s\n |    O\n |   /|\\ \n |    |\n |\n |             ", letras_erradas_string);
      break;
    case 5:
      printf(" ______\n |    |        %s\n |    O\n |   /|\\ \n |    |\n |   /\n |             ", letras_erradas_string); 
      break;
    case 6:
      printf(" ______\n |    |        %s\n |    O\n |   /|\\ \n |    |\n |   / \\ \n |             ", letras_erradas_string); 
      break;
  }
}

void printarPalavra() {
  for (int i = 0; i < tamanho; i++) {
    cout << toUpperCase(letras_acertadas[i]) << " ";
  }
}

int main() {
  srand(static_cast<unsigned int>(time(0)));
  system(CLEAR);

  palavra_aleatoria = sortearPalavra();
  tamanho = palavra_aleatoria.length();

  for (int i = 0; i < tamanho; i++) {
    letras_acertadas[i] = '_';
  }

  char letra;
  while(erros < 6 && !verificarVitoria()) {
    printarBoneco();
    printarPalavra();
    letra = toLowerCase(pedirLetra());
    verificarLetraNaPalavra(letra);
    system(CLEAR);
  }

  printarBoneco();
  printarPalavra();
  if (erros == 6) {
    cout << "\n\nPoxa...";
  } else {
    cout << "\n\nParabéns, você ganhou!";
  }
  cout << " A palavra era \"" + palavra_aleatoria + "\"\n";

  return 0;
}