#ifndef CARD_H
#define CARD_H

#include <stdlib.h>

typedef struct Card {
    char rank;  // 'A', '2'-'9', 'T', 'J', 'Q', 'K'
    char suit;  // 'C', 'D', 'H', 'S'
    struct Card* next;
} Card;

typedef struct {
    Card* head;
    int size;
} CardList;

void init_deck(CardList* deck);
void load_deck_from_file(CardList* deck, const char* filename);
void shuffle_deck(CardList* deck);
void free_deck(CardList* deck);

#endif //CARD_H
