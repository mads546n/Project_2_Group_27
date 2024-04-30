//
// Created by Caspe on 22-04-2024.
//
#ifndef PROJECT_2_MODEL_H
#define PROJECT_2_MODEL_H


#include "../view/view.h"

void initializeSampleDeck(Card deck[]);
void distributeDeckToColumns(Card deck[], ListNode* columns[]);
Card* split(Card Deck[], int x);
void printDeck(Card deck[]);


void startDeck ();

#endif //PROJECT_2_MODEL_H
