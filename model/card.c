#include <stdio.h>
#include <stdlib.h>
#include "card.h"

// Function used to initialize a new column
Column *createColumn() {
    Column *column = (Column *)malloc(sizeof(Column));
    if (column == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    column->top = NULL;
    return column;
}

// Function used to push a card onto the top of a column
void push(Column *column, char suit, char rank) {
    Card *newCard = (Card *)malloc(sizeof(Card));
    if (newCard == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newCard->suit = suit;
    newCard->rank = rank;
    newCard->next = column->top;
    column->top = newCard;
}

// Function to print the contents of a column
void printColumn(Column *column) {
    Card *current = column->top;
    while (current != NULL) {
        printf("[%c%d] ", current->suit, current->rank);
        current = current->next;
    }
    printf("\n");
}

// Function to free allocated memory from a column
void freeColumn(Column *column) {
    Card *current = column->top;
    while (current != NULL) {
        Card *temp = current;
        current = current->next;
        free(temp);
    }
    free(column);
}

int getDeckSize(Card *deck) {
    int size = 0;
    Card *current = deck;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

// Function to distribute cards among columns (currently evenly)
void distributeCards(Card *deck, Column *columns[], int numColumns) {

    // Calculate size of deck
    int deckSize = getDeckSize(deck);

    // Calculate amount of cards per column
    int cardsPerColumn = (deckSize + numColumns - 1) / numColumns; // Round up result

    int columnIndex = 0;
    int cardsRemaining = deckSize;

    // Iterate through the deck
    while (deck != NULL && columnIndex < numColumns) {

        // Push card into the current column
        push(columns[columnIndex], deck->suit, deck->rank);

        // Move to next card in deck
        Card *temp = deck;
        deck = deck->next;
        free(temp); // Free the card. It's now a part of the column

        // Update remaining cards
        cardsRemaining--;

        // Move to next column if current is full
        if (cardsRemaining % cardsPerColumn == 0) {
            columnIndex++;
        }
    }
}

// Function to initialize a sample deck
void initializeSampleDeck(Card columns[][13]) {
    for (int col = 0; col < 7; col++) {
        for (int row = 0; row < 13; row++) {
            columns[col][row].rank = 'O' + row + 2;
            columns[col][row].suit = 'H';
        }
    }
}
