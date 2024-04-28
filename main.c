#include <stdio.h>
#include "view/view.h"
#include "model/model.h"

int main() {
    // Initialize a deck
    Card deck[52];
    initializeSampleDeck(deck);

    // Printing sample deck
    printf("Original deck:\n");
    printDeck(deck);
    printf("\n");

    int x = 26; // Example of split-time
    Card* shuffleDeck = split(deck, x);

    printf("\nShuffled deck:\n");
    printDeck(shuffleDeck);
    printf("\n");

    // Arrays of pointer to the head of each column and foundation
    ListNode* columns[7] = {NULL};
    FoundationNode* foundations[4] = {NULL};

    char message[50] = "";

    char lastCommand[50] = "";

    bool isEmpty = true; // Flag to indicate if the game board is empty

    printf("Deck initialized and distributed in columns... \n");
    distributeDeckToColumns(deck, columns);
    for (int i = 0; i < 7; i++) {
        ListNode* current = columns[i];
        while (current != NULL) {
            printf("[%c%c] ", current->card.rank, current->card.suit);
            current = current->next;
        }
        printf("\n");
    }

    while (1) {

        // Display the game board
        displayBoard(columns, foundations, isEmpty, message, lastCommand);

    }

    return 0;



}
