//
// Created by edvar on 23-04-2024.
//

#ifndef PROJECT_2_CARD_H
#define PROJECT_2_CARD_H

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

// Function prototypes for card.c
Card* createCard(char rank, char suit);
void freeCard(Card *card);
Column* createColumn();
void push(Column *column, char suit, char rank);
void printColumn(Column *column);
void freeColumn(Column *column);
void initializeSampleDeck(Card columns[][13]);

#endif //PROJECT_2_CARD_H