#ifndef VIEW_H
#define VIEW_H

#include <stdbool.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_MESSAGE_LENGTH 100

extern char message[MAX_MESSAGE_LENGTH]; //Store message for display

typedef struct Card {
    char rank;
    char suit;
    struct ListNode* next; // Pointer to the next card in the linked list
} Card;

typedef struct ListNode {
    Card card;
    struct ListNode* next;
} ListNode;

typedef struct FoundationNode {
    Card card;
    struct FoundationNode* next;
} FoundationNode;

void displayBoard(ListNode* columns[], FoundationNode* foundations[], bool areColumnsEmpty, char* message, char* lastCommand);

#endif /* VIEW_H */
