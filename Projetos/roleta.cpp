#include <iostream>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;

#ifdef _WIN32
  #define CLEAR "cls"
  #include <Windows.h>
#else
  #include <unistd.h>
  #define CLEAR "clear"
#endif

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define TEXT_WHITE "\033[38m"
#define RED "\033[48;5;124m"
#define GREEN TEXT_WHITE "\033[48;5;22m"
#define BLACK RESET
#define DEFAULT "\033[48;5;237m"
#define EMPTY_LINE DEFAULT "                                                 \n" RESET

#define QNT 40

typedef struct {
  int number;
  const char* color;
} Pocket;

struct node {
  Pocket pocket;
  struct node *next;
  struct node *prev;
};
typedef struct node* nodePtr;

void customSleep(int timeInMicroSeconds) {
  #ifdef _WIN32
    Sleep(timeInMicroSeconds / 1000);
  #else
    usleep(timeInMicroSeconds);
  #endif
}

bool isWheelEmpty(nodePtr finalPtr) {
  return !finalPtr;
}

void insertPocket(nodePtr* finalPtr, int* qntPtr, Pocket pocket) {
  nodePtr newNode = new node;
  newNode->pocket = pocket;

  if (!isWheelEmpty(*finalPtr)) {
    newNode->next = (*finalPtr)->next;
    newNode->prev = (*finalPtr);
    (*finalPtr)->next->prev = newNode;
    (*finalPtr)->next = newNode;
  } else {
    newNode->next = newNode;
    newNode->prev = newNode;
  }

  *finalPtr = newNode;
  (*qntPtr)++;
}

void initializePositions(int* positions[15]) {
  int sizes[15] = {5, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 5};
  for (int i = 0; i < 15; i++) {
    positions[i] = (int*)malloc(sizes[i] * sizeof(int));
  }

  int value1 = 0, value2 = QNT-1;
  for (int i = 0; i < 13; i++) {
    for (int j = sizes[i] / 2; j < sizes[i]; j++) {
      positions[i][j] = value1++;
    }
  }
  for (int i = 0; i < 13; i++) {
    for (int j = (sizes[i] / 2) - 1; j >= 0; j--) {
      positions[i][j] = value2--;
    }
  }
  positions[13][0] = value2--;
  positions[13][1] = value2--;
  for (int i = 0; i < 5; i++) {
    positions[14][i] = value2--;
  }
  positions[13][2] = value2--;
  positions[13][3] = value2--;
}

void printPocket(Pocket pocket) {
  printf("%s%2d %s", pocket.color, pocket.number, RESET);
}

void printLine1(Pocket wheel[], int positions[5]) {
  printf(DEFAULT);printf("                 ");printf(RESET);
  printPocket(wheel[positions[0]]);
  printPocket(wheel[positions[1]]);
  printPocket(wheel[positions[2]]);
  printPocket(wheel[positions[3]]);
  printPocket(wheel[positions[4]]);
  printf(DEFAULT);printf("                 \n");printf(RESET);
}

void printLine2(Pocket wheel[], int positions[4]) {
  printf(DEFAULT);printf("           ");printf(RESET);
  printPocket(wheel[positions[0]]);
  printPocket(wheel[positions[1]]);
  printf(DEFAULT);printf("      %s       ", positions[0] > 30 ? "⚪" : "  ");printf(RESET);
  printPocket(wheel[positions[2]]);
  printPocket(wheel[positions[3]]);
  printf(DEFAULT);printf("           \n");printf(RESET);
}

void printLine3(Pocket wheel[], int positions[2]) {
  printf(DEFAULT);printf("        ");printf(RESET);
  printPocket(wheel[positions[0]]);
  printf(DEFAULT);printf("                           ");printf(RESET);
  printPocket(wheel[positions[1]]);
  printf(DEFAULT);printf("        \n");printf(RESET);
}

void printLine4(Pocket wheel[], int positions[2]) {
  printf(DEFAULT);printf("     ");printf(RESET);
  printPocket(wheel[positions[0]]);
  printf(DEFAULT);printf("                                 ");printf(RESET);
  printPocket(wheel[positions[1]]);
  printf(DEFAULT);printf("     \n");printf(RESET);
}

void printLine5(Pocket wheel[], int positions[2]) {
  printf(DEFAULT);printf("  ");printf(RESET);
  printPocket(wheel[positions[0]]);
  printf(DEFAULT);printf("                                       ");printf(RESET);
  printPocket(wheel[positions[1]]);
  printf(DEFAULT);printf("  \n");printf(RESET);
}

void printWheel(nodePtr finalPocketPtr) {
  system(CLEAR);

  Pocket wheel[QNT];
  nodePtr aux = finalPocketPtr->next;
  for (int i = 0; i < QNT; i++) {
    wheel[i] = aux->pocket;
    aux = aux->next;
  }

  int* positions[15];
  initializePositions(positions);

  printf(EMPTY_LINE);
  printf(EMPTY_LINE);
  printLine1(wheel, positions[0]);
  printLine2(wheel, positions[1]);
  printLine3(wheel, positions[2]);
  printLine4(wheel, positions[3]);
  printLine4(wheel, positions[4]);
  printLine5(wheel, positions[5]);
  printLine5(wheel, positions[6]);
  printLine5(wheel, positions[7]);
  printLine5(wheel, positions[8]);
  printLine5(wheel, positions[9]);
  printLine4(wheel, positions[10]);
  printLine4(wheel, positions[11]);
  printLine3(wheel, positions[12]);
  printLine2(wheel, positions[13]);
  printLine1(wheel, positions[14]);
  printf(EMPTY_LINE);
}

void initializeWheel(nodePtr* finalPocketPtr, int* pocketsQnt ) {
  Pocket pocket;

  int numbers[QNT];
  for (int i = 0; i < QNT; i++) { numbers[i] = i; }
  random_device rd;
  mt19937 g(rd());
  shuffle(numbers, numbers + QNT, g);

  for (int i = 0; i < QNT; i++) {
    pocket.number = numbers[i];
    if (pocket.number == 0) {
      pocket.color = GREEN;
    } else if (i % 2 == 0) {
      pocket.color = RED;
    } else {
      pocket.color = BLACK;
    }

    insertPocket(finalPocketPtr, pocketsQnt, pocket);
  }
}

void spinWheel(nodePtr* finalPocketPtr, int spinsQnt, int chosenNumber) {
  for (int i = 0; i < spinsQnt; i++) {
    printWheel(*finalPocketPtr);
    printf(EMPTY_LINE);
    printf(DEFAULT);printf(BOLD);printf("                Número  escolhido:               \n");printf(RESET);
    printf(DEFAULT);printf("               %s         %2d         %s              \n", BLACK, chosenNumber, DEFAULT);printf(RESET);
    printf(EMPTY_LINE);
    printf(EMPTY_LINE);

    *finalPocketPtr = (*finalPocketPtr)->prev;

    if (i < 0.40*spinsQnt) { // 0%-40%
      customSleep(125000);
    } else if (i < 0.60*spinsQnt) { // 40%-60%
      customSleep(175000);
    } else if (i < 0.65*spinsQnt) { // 60%-65%
      customSleep(225000);
    } else if (i < 0.80*spinsQnt) { // 65%-80%
      customSleep(275000);
    } else if (i < 0.90*spinsQnt) { // 80%-90%
      customSleep(375000);
    } else if (i < 0.95*spinsQnt) { // 90%-95%
      customSleep(550000);
    } else { // 95%-100%
      customSleep(800000);
    }
  }
  customSleep(500000);
}

int askUser() {
  int chosenNumber;

  printf(EMPTY_LINE);
  printf(DEFAULT);printf(BOLD);printf("                Escolha um número:               \n");printf(RESET);
  printf(DEFAULT);printf("               %s                    %s              \n", BLACK, DEFAULT);printf(RESET);
  printf(EMPTY_LINE);
  printf(EMPTY_LINE);
  printf("\033[3F\033[24C");
  scanf("%d", &chosenNumber);

  return chosenNumber;
}

void start(nodePtr* finalPocketPtr) {
  int
    minSpins = 35,
    maxSpins = 120,
    spinsQnt = (rand() % (maxSpins - minSpins)) + minSpins;
  
  printWheel(*finalPocketPtr);

  int chosenNumber = askUser();
  if (chosenNumber < 0 || chosenNumber > 39) return;

  spinWheel(finalPocketPtr, spinsQnt, chosenNumber);

  Pocket winningPocket = (*finalPocketPtr)->next->pocket;

  printWheel(*finalPocketPtr);
  printf(EMPTY_LINE);
  printf(DEFAULT);printf(BOLD);
  if (winningPocket.number == chosenNumber) {
    printf("            PARABÉNS! 🎉 Você venceu!            \n");
  } else {
    printf("       Não foi dessa vez! O resultado foi:       \n");
  }
  printf(RESET);
  printf(DEFAULT);printf("               %s         %2d         %s              \n", BLACK, winningPocket.number, DEFAULT);printf(RESET);
  if (winningPocket.number != chosenNumber) {
    printf(EMPTY_LINE);
    printf(DEFAULT);printf(BOLD);printf("            E o número escolhido foi:            \n");printf(RESET);
    printf(DEFAULT);printf("               %s         %2d         %s              \n", BLACK, chosenNumber, DEFAULT);printf(RESET);
  }
  printf(EMPTY_LINE);
  printf(EMPTY_LINE);
}

int main() {
  srand(time(NULL));

  nodePtr finalPocket = NULL;
  int pocketsQnt = 0;
  
  initializeWheel(&finalPocket, &pocketsQnt);
  start(&finalPocket);
}