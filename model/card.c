#include <stdio.h>
#include <stdlib.h>
#include "card.h"

// Define the structure of a card
typedef struct Card {
    char rank;
    char suit;
    struct Card *next;
} Card;

// Define the structure of a column
typedef struct Column {
    Card *top; // Create a pointer to the top card of the column
} Column;

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

// Function to distribute cards among columns (currently evenly)
void distributeCards(Card *deck, Column *columns[], int numColumns) {

    // Calculate amount of cards per column
    int cardsPerColumn = (DECK_SIZE + numColumns - 1) / numColumns; // Round up result

    int columnIndex = 0;
    int cardsRemaining = DECK_SIZE;

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

// Sample game state to test functionality
int testmain() {
    Column *columns[7]; //Array of pointers to columns
    for (int i = 0; i < 7; i++) {
        columns[i] = createColumn(); // Initialize each of the columns
    }

    // Push cards into the columns
    push(columns[0], 'H', '5');
    push(columns[0], 'D', '1');
    push(columns[1], 'S', 'Q');

    // Print content of columns
    printf("Displaying columns:\n");
    for (int i = 0; i < 7; i++) {
        printf("Column %d: ", i + 1);
        printColumn(columns[i]);
    }

    // Free allocated memory
    for (int i = 0; i < 7; i++) {
        freeColumn(columns[i]);
    }

    return 0;
}

