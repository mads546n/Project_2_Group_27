#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/model.h"  // Assuming model.h declares Card, ListNode, and FoundationNode

typedef enum {
    STARTUP,
    PLAY
} GamePhase;

typedef struct {
    GamePhase phase;
    Card* deck;
    ListNode* columns[7];
    FoundationNode* foundations[4];
    char message[256];
    char lastCommand[50];
} GameState;

void processCommand(char* command, GameState* gameState);

#endif
