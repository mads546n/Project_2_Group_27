#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

// Structure to represent a card
typedef struct Card {
    char rank;
    char suit;
} Card;

// Function prototype for displaying the game board
void displayBoard(Card columns[][7], Card foundations[], bool isEmpty, char* message);

#endif /* BOARD_H */
