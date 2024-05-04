#ifndef MODEL_H
#define MODEL_H

#include <stdbool.h>

typedef struct Deck {
    char* card;
    struct Deck* next;
} Deck;

typedef struct Card {
    char rank;
    char suit;
} Card;

typedef struct ListNode {
    Card card;
    struct ListNode* next;
} ListNode;

typedef struct FoundationNode {
    Card card;
    struct FoundationNode* next;
} FoundationNode;

void insertStart(Deck** head, char* card);
void insertEnd(Deck** head, char* card);
void initializeSampleDeck(Card deck[]);
void shuffleDeck(Card deck[]);

#endif //MODEL_H
