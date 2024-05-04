#include "model/model.h"
#include <malloc.h>
#include <stdio.h>

void insertStart(Deck** head, char* card) {
    Deck* newNode = (Deck*)malloc(sizeof(Deck));
    newNode->card = card;
    newNode->next = *head;
    *head = newNode;
}

void insertEnd(Deck** head, char* card) {
    Deck* newNode = (Deck*)malloc(sizeof(Deck));
    newNode->card = card;
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
    } else {
        Deck* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}
