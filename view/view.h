#ifndef VIEW_H
#define VIEW_H

#include <stdbool.h>

typedef struct Card {
    char rank;
    char suit;
    struct Card* next;
} Card;

void displayBoard(Card columns[][7], bool areColumnsEmpty, char* message);

#endif /* VIEW_H */
