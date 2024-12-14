/*
  Nota: Os emojis de baralho têm uma aparência mais bonita
  quando o sistema operacional utilizado é Linux
*/

#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

#ifdef _WIN32
  #define CLEAR "cls"
#else
  #define CLEAR "clear"
#endif

#define TEXT_RED "\033[38;5;124m"
#define TEXT_WHITE "\033[37m"
#define TEXT_BLUE "\033[30m"
#define BOLD "\033[1m"
#define RESET "\033[0m"

const char* suitCards[4][14] = {
  {"🂡", "🂢", "🂣", "🂤", "🂥", "🂦", "🂧", "🂨", "🂩", "🂪", "🂫", "🂭", "🂮"},
  {"🃑", "🃒", "🃓", "🃔", "🃕", "🃖", "🃗", "🃘", "🃙", "🃚", "🃛", "🃝", "🃞"},
  {"🂱", "🂲", "🂳", "🂴", "🂵", "🂶", "🂷", "🂸", "🂹", "🂺", "🂻", "🂽", "🂾"},
  {"🃁", "🃂", "🃃", "🃄", "🃅", "🃆", "🃇", "🃈", "🃉", "🃊", "🃋", "🃍", "🃎"}
};

// ♠Espadas: 0, ♣Paus: 1, ♥Copas: 2, ♦Ouros: 3
typedef struct {
  int number;
  int suit;
} Card;

typedef struct {
  Card card;
  bool isEmpty;
} CardSlot;

struct node {
  Card card;
  struct node *next;
  struct node *prev;
};
typedef struct node* nodePtr;

#define STACKS_QNT 8
nodePtr tableau[STACKS_QNT];
CardSlot freeCells[4];
CardSlot foundations[4];

bool isStackEmpty(int stackIndex) {
  return !tableau[stackIndex];
}

void addCardToStack(Card card, int stackIndex) {
  nodePtr newNode;
  newNode = (nodePtr) malloc (sizeof (struct node));
  newNode->card = card;
  newNode->next = tableau[stackIndex];
  newNode->prev = NULL;
  if (tableau[stackIndex] != NULL) {
    tableau[stackIndex]->prev = newNode;
  }
  tableau[stackIndex] = newNode;
}

void removeCardFromStack(int stackIndex) {
  if (isStackEmpty(stackIndex)) {
    return;
  }

  tableau[stackIndex] = tableau[stackIndex]->next;
  
  if (!isStackEmpty(stackIndex)) {
    tableau[stackIndex]->prev = NULL;
  }
}

void initializeTableau() {
  int numbers[52];
  for (int i = 0; i < 52; i++) {
    numbers[i] = i;
  }

  random_device rd;
  mt19937 g(rd());
  shuffle(numbers, numbers + 52, g);

  for (int i = 0; i < 52; i++) {
    Card currentCard = {
      numbers[i] % 13,
      numbers[i] / 13
    };
    addCardToStack(currentCard, i % STACKS_QNT);
  }

  CardSlot emptyCardSlot = { {0, 0}, true };
  for (int i = 0; i < 4; i++) {
    freeCells[i] = emptyCardSlot;
    foundations[i] = emptyCardSlot;
  }
}

void printCard(Card card) {
  if (card.suit < 2) {
    printf(TEXT_WHITE);
  } else {
    printf(TEXT_RED);
  }
  printf(BOLD);
  printf("%s  ", suitCards[card.suit][card.number]);
  printf(RESET);
}

void printTableau() {
  system(CLEAR);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == 1 && j == 0) {
        printf("  ");
      }
      
      CardSlot currentSlot = (i == 0) ? freeCells[j] : foundations[j];
      if (!currentSlot.isEmpty) {
        printCard(currentSlot.card);
      } else {
        printf(TEXT_BLUE);
        printf(BOLD);
        printf("🂠  ");
        printf(RESET);
      }
    }
  }
  printf("\n\n");

  printf("%s 1  2  3  4  5  6  7  8\n%s", BOLD, RESET);

  bool allNull = false;
  int i = 0;
  while (!allNull) {
    allNull = true;

    for (int j = 0; j < STACKS_QNT; j++) {
      nodePtr curNodePtr = tableau[j];
      if (!curNodePtr) {
        if (j == 0) printf(" ");
        printf("   ");
        continue;
      }

      while (curNodePtr->next) {
        curNodePtr = curNodePtr->next;
      }
      for (int k = i; k > 0; k--) {
        curNodePtr = curNodePtr ? curNodePtr->prev : NULL;
      }

      if (j == 0) printf(" ");
      if (curNodePtr) {
        allNull = false;
        printCard(curNodePtr->card);
      } else {
        printf("   ");
      }
    }

    printf("\n");
    i++;
  }
}

void moveCard(int from, int to) { // tableau: 0 - 7; freeCells: -1 - -4
  int freeCellFromIndex = (from * -1) - 1;
  int freeCellToIndex = (to * -1) - 1;

  if (from >= 0 && isStackEmpty(from)) {
    return;
  }
  if (to >= 0 && isStackEmpty(to)) {
    Card cardToMove = from < 0
      ? freeCells[freeCellFromIndex].card
      : tableau[from]->card;

    if (from < 0) {
      freeCells[freeCellFromIndex] = { {0, 0}, true };
    } else {
      removeCardFromStack(from);
    }

    addCardToStack(cardToMove, to);
    return;
  }

  Card cardToMove = from < 0
    ? freeCells[freeCellFromIndex].card
    : tableau[from]->card;
  Card otherCard = to < 0
    ? freeCells[freeCellToIndex].card
    : tableau[to]->card;

  if (
    (
      cardToMove.number == otherCard.number-1 &&
      (
        cardToMove.suit > 1 && otherCard.suit < 2 ||
        cardToMove.suit < 2 && otherCard.suit > 1
      )
    ) ||
    (
      to < 0 && freeCells[freeCellToIndex].isEmpty
    ) ||
    (
      to >= 0 && isStackEmpty(to)
    )
  ) {
    if (from < 0) {
      freeCells[freeCellFromIndex] = { {0, 0}, true };
    } else {
      removeCardFromStack(from);
    }
    if (to < 0) {
      freeCells[freeCellToIndex] = { cardToMove, false };
    } else {
      addCardToStack(cardToMove, to);
    }
  }
}

bool verifyFoundations() {
  bool cardWasMoved = true;
  while (cardWasMoved) {
    cardWasMoved = false;

    for (int i = 0; i < STACKS_QNT; i++) {
      if (!tableau[i]) continue;

      Card curCard = tableau[i]->card;
      if (
        (curCard.number == 0 && foundations[curCard.suit].isEmpty) ||
        (!foundations[curCard.suit].isEmpty && foundations[curCard.suit].card.number == curCard.number-1)
      ) {
        removeCardFromStack(i);
        foundations[curCard.suit] = { curCard, false };
        cardWasMoved = true;
      }
    }
  }

  for (int i = 0; i < 4; i++) {
    if (foundations[i].card.number != 12) {
      return false;
    }
  }
  return true;
}

void askUser() {
  char escolha1, escolha2;
  printf("1-8 para as pilhas (1-8)\n");
  printf("A-D para as free cells (A-D)\n");
  printf("Formato: 'Origem Destino' (ex: '3 5' para mover da coluna 3 para a 5)\n");
  printf("Escolha uma carta para mover: ");
  cin >> escolha1 >> escolha2;

  bool isValid = true;
  int origem, destino;
  if (escolha1 >= 'A' && escolha1 <= 'D') {
    origem = -(escolha1 - 'A' + 1);
  } else if (escolha1 >= '1' && escolha1 <= '8') {
    origem = escolha1 - '1';
  } else {
    isValid = false;
  }

  if (escolha2 >= 'A' && escolha2 <= 'D') {
    destino = -(escolha2 - 'A' + 1);
  } else if (escolha2 >= '1' && escolha2 <= '8') {
    destino = escolha2 - '1';
  } else {
    isValid = false;
  }
  
  if (isValid) {
    moveCard(origem, destino);
  }
}

int main() {  
  initializeTableau();
  verifyFoundations();
  do {
    printTableau();
    askUser();
  } while(!verifyFoundations());
  printTableau();
  printf("PARABÉEENSS!! VOCÊ CONSEGUIU!");
}