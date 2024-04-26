#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
    int columnIndex = 0;
    int faceDownCards = 21;

    while (deck != NULL) {
        bool isFaceDown = faceDownCards > 0;

        push(columns[columnIndex], deck->suit, deck->rank);

        if (isFaceDown) {
            faceDownCards--;
        }

        columnIndex++;

        if (columnIndex >= numColumns) {
            columnIndex = 0;
        }

        Card *temp = deck;
        deck = deck->next;
        free(temp);
    }
}

// Function to initialize a sample deck
void initializeSampleDeck(Card *deck) {
    char suits[] = {'H', 'D', 'C', 'S'};
    int index = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 2; j <= 14; j++) {
            deck[index].suit = suits[i];
            deck[index].rank = j;
            index++;
        }
    }
}
