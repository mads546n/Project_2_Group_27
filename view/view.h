#ifndef VIEW_H
#define VIEW_H

#include "../model/model.h"
#include <malloc.h>
#include <stdio.h>

void printDeck(Card* deck);
void displayBoard(ListNode* columns[], FoundationNode* foundations[], bool isEmpty, char message[], char lastCommand[]);

#endif //VIEW_H