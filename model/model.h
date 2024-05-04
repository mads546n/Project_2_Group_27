#ifndef MODEL_H
#define MODEL_H

#include <stdbool.h>

typedef struct Deck {
    char* card;
    struct Deck* next;
} Deck;

void insertStart(Deck** head, char* card);
void insertEnd(Deck** head, char* card);

#endif //MODEL_H
