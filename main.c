#include <stdio.h>
#include "view/view.h"
#include "model/model.h"
#include "controller/controller.h"

int main() {
    // Initialize a deck
    Card deck[52];
    initializeSampleDeck(deck);

    // Printing sample deck
    printf("Original deck:\n");
    printDeck(deck);
    printf("\n");

    // Arrays of pointer to the head of each column and foundation
    ListNode *columns[7] = {NULL};
    FoundationNode *foundations[4] = {NULL};

    char message[50] = "";

    char lastCommand[50] = "";

    bool isEmpty = true; // Flag to indicate if the game board is empty

    distributeDeckToColumns(deck, columns);

    printf("Shuffled deck: \n");
    shuffleDeck(deck);
    for (int i = 0; i < 52; i++) {
        printf("[%c%c] ", deck[i].rank, deck[i].suit);
    }
    printf("\n");
    printf("\n");

    while (1) {

        // Display the game board
        displayBoard(columns, foundations, isEmpty, message, lastCommand);

        //Important
        *columns = NULL;
    }

}