#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void initializeDeck(Card** deck) {
    // Initialize a standard deck of cards
}

void loadDeck(Card** deck, const char* filename) {
    // Load cards from a file
}

void shuffleDeck(Card** deck) {
    // Implement a Fisher-Yates shuffle for the linked list
}

void interleaveDeck(Card** deck, int split) {
    // Implement interleaving based on a split index
}

void displayDeck(Card* deck) {
    // Print all cards in the deck
}

void startGame(Card** deck, Card* columns[]) {
    // Distribute cards into columns to start the game
}

void freeDeck(Card* deck) {
    // Free all cards in the deck
}
