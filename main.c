#include "view/view.h"
#include "model/model.h"
#include "controller/controller.h"
#include <stdio.h>
#include <string.h>

int main() {
    Card deck[52];
    initializeSampleDeck(deck);

    printf("Original deck:\n");
    printDeck(deck);
    printf("\n");

    Card *shuffledDeck = shuffle(deck, 15);
    printf("Shuffled Deck:\n");
    printDeck(shuffledDeck);
    printf("\n");

    ListNode *columns[7] = {NULL};
    FoundationNode *foundations[4] = {NULL};

    distributeDeckToColumns(shuffledDeck, columns);

    char message[100] = "Welcome to Yukon Solitaire!";
    char lastCommand[100] = "";

    while (1) {
        displayBoard(columns, foundations, message, lastCommand);

        bool exitGame = processInput(columns, foundations, message, lastCommand);
        if (exitGame) break;

        strcpy(message, "");
    }

    freeDeck(shuffledDeck);
    freeGameResources(columns, foundations);

    return 0;
}
