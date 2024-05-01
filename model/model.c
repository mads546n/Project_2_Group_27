// model.c
#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node* loadDeckFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: File does not exist.\n");
        return NULL;
    }

    Node *head = NULL, *current = NULL;
    char buffer[3];
    while (fscanf(file, "%2s", buffer) == 1) {
        Node* newCard = (Node*)malloc(sizeof(Node));
        strcpy(newCard->card, buffer);
        newCard->next = NULL;
        if (!head) {
            head = newCard;
        } else {
            current->next = newCard;
        }
        current = newCard;
    }
    fclose(file);
    return head;
}

void freeLinkedList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
