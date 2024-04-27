#include "model.h"
#include "../controller/controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../view/view.h"

//Linked list structure.
struct Deck {
    char* card;
    struct Deck* next;
};
char buffer[3][51];

void insertStart(struct Deck** head, char* card){
    //Allocates memory for the linked list using malloc.
    struct Deck* newNode
            = (struct Deck*)malloc(sizeof(struct Deck));
    // store the card in the new Deck
    newNode->card = card;
    // the next pointer of new Deck will be on current head
    newNode->next = *head;
    // the current head will the new Deck
    *head = newNode;
}

void insertEnd(struct Deck** head, char* card){
    struct Deck* newNode
            = (struct Deck*)malloc(sizeof(struct Deck));
//    printf("size of malloc is%llu",sizeof(struct Deck));

    // store the card in the new Deck
    newNode->card = card;
    // Since the node will be last its next will be NULL
    newNode->next = NULL;
    // in case this is the first node make the newNode as
    // the head of the LinkedList
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    // Create a pointer to iterate till the last node
    struct Deck* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    // make the next of the tail to the new Deck
    current->next = newNode;
}
void printList(struct Deck* head){
    struct Deck* current = head;
    while (current != NULL) {
        printf("%s", current->card);
        current = current->next;
    }
}

void command (const char* chr){
    int i = 1;
    struct Deck* head = NULL;
    //Checks for LD command.
    if (strcmp(chr, "LD") == 0) {
        //Checks if the LD command has a path name.
        if (strlen(chr)==2){
            char *filename = "../model/cards.txt";
            FILE* fp = fopen(filename, "r");
            char ch[105];

            // Assigns the cards from the fget buffer into the array so they are saved and then assigns them to a linked list.
            bool first = true;
            while (fgets(ch, 105, fp) !=NULL){
                if(first){
                    strcpy(buffer[0],ch);
                insertStart(&head, buffer[0]);
                first=false;
                } else {
                    strcpy(buffer[i],ch);
                    insertEnd(&head, buffer[i++]);
                }
            }
        }
    }
//    Card columns[7][7];
//    displayBoard(columns,false,"OK");
//Prints linked list.
    printList(head);
}

