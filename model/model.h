#ifndef MODEL_H
#define MODEL_H

#include "../card/card.h"

void initializeDeck(Card** deck);
void loadDeck(Card** deck, const char* filename);
void shuffleDeck(Card** deck);
void interleaveDeck(Card** deck, int split);
void displayDeck(Card* deck);
void startGame(Card** deck, Card* columns[]);
void freeDeck(Card* deck);

#endif /* MODEL_H */
