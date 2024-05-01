// model.h
#ifndef MODEL_H
#define MODEL_H

typedef struct Node {
    char card[3];  // Card representation: "5D", "KH", etc.
    struct Node* next;
} Node;

Node* loadDeckFromFile(const char* filename);
void freeLinkedList(Node* head);

#endif
