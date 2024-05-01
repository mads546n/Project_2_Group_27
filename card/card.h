#ifndef CARD_H
#define CARD_H

typedef struct {
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

#endif /* CARD_H */
