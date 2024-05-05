
//
// Created by edvar on 21-04-2024.
//

#include <malloc.h>
#include <stdio.h>
#include <time.h>
#include <intrin.h>
#include "../view/view.h"
#include "model.h"
#include "../controller/controller.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

//void startDeck (){
//    int i = 1;
//    struct Deck* head = NULL;
//    //Checks for LD startDeck.
//    //Checks if the LD startDeck has a path name.
//    char *filename = "../model/cards.txt";
//    FILE *fp = fopen(filename, "r");
//    char ch[105];
//    // Assigns the cards from the fget buffer into the array so they are saved and then assigns them to a linked list.
//    bool first = true;
//    while (fgets(ch, 105, fp) != NULL) {
//        if (first) {
//            strcpy(buffer[0], ch);
//            insertStart(&head, buffer[0]);
//            first = false;
//        } else {
//            strcpy(buffer[i], ch);
//            insertEnd(&head, buffer[i++]);
//        }
//    }
//}


// Function to initialize a sample deck
void initializeSampleDeck(Card deck[], char* filename, ListNode* columns[]) {

    int i = 1;
    struct Deck* head = NULL;
    //Checks for LD startDeck.
    //Checks if the LD startDeck has a path name.
//    char *filename = "../model/cards.txt";
    FILE *fp = fopen(filename, "r");
    char ch[105];
    // Assigns the cards from the fget buffer into the array so they are saved and then assigns them to a linked list.
    bool first = true;
    while (fgets(ch, 105, fp) != NULL) {
        if (first) {
            strcpy(buffer[0], ch);
            insertStart(&head, buffer[0]);
            deck[0].suit = buffer[0][1];
            deck[0].rank = buffer[0][0];
            first = false;
        } else {
            strcpy(buffer[i], ch);
            deck[i].suit = buffer[i][1];
            deck[i].rank = buffer[i][0];
            insertEnd(&head, buffer[i++]);

        }
    }
    fclose(fp);

    printf("\n");
    first = false;

    distributeDeckToColumns(deck, columns);
    bool cardAdded[52] = { false };
    int index = 0;
    for (int i = 0; i < 7; i++) {
        ListNode* currentColumn = NULL;
        int cardsToAdd = (i == 0) ? 1 : i + 5; // Determine number of cards to be distributed in each column
        for (int j = 0; j < cardsToAdd && index < 52; j++) {
            while (index < 52 && cardAdded[index]) {
                index++;
            }
            if (index < 52) {
                ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
                if (newNode == NULL) {
                    fprintf(stderr,"Memory allocation failed\n");
                    while (currentColumn != NULL) {
                        ListNode* temp = currentColumn;
                        currentColumn = currentColumn->next;
                        free(temp);
                    }
                    return;
                }
                newNode->card = deck[index];
                newNode->next = currentColumn;
                currentColumn = newNode;
                cardAdded[index] = true;
            }
        }
        columns[i] = currentColumn;
    }
}

void load(Card deck[], char* argument) {
//
//    int i = 1;
//    struct Deck* head = NULL;
//    //Checks for LD startDeck.
//    //Checks if the LD startDeck has a path name.
//    char *file;
//    strcpy ( file,argument)
//    char *filename = "../model/%s",file;
//    FILE *fp = fopen(filename, "r");
//    char ch[105];
//    // Assigns the cards from the fget buffer into the array so they are saved and then assigns them to a linked list.
//    bool first = true;
//    while (fgets(ch, 105, fp) != NULL) {
//        if (first) {
//            strcpy(buffer[0], ch);
//            insertStart(&head, buffer[0]);
//            deck[0].suit = buffer[0][1];
//            deck[0].rank = buffer[0][0];
//            first = false;
//        } else {
//            strcpy(buffer[i], ch);
//            deck[i].suit = buffer[i][1];
//            deck[i].rank = buffer[i][0];
//            insertEnd(&head, buffer[i++]);
//
//        }
//    }
//    printf("\n");
}


// Function to distribute a given card deck along the columns
void distributeDeckToColumns(Card deck[], ListNode* columns[]) {
    bool cardAdded[52] = { false };
    int index = 0;
    for (int i = 0; i < 7; i++) {
        ListNode* currentColumn = NULL;
        int cardsToAdd = (i == 0) ? 1 : i + 5; // Determine number of cards to be distributed in each column
        for (int j = 0; j < cardsToAdd && index < 52; j++) {
            while (index < 52 && cardAdded[index]) {
                index++;
            }
            if (index < 52) {
                ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
                if (newNode == NULL) {
                    fprintf(stderr,"Memory allocation failed\n");
                    while (currentColumn != NULL) {
                        ListNode* temp = currentColumn;
                        currentColumn = currentColumn->next;
                        free(temp);
                    }
                    return;
                }
                newNode->card = deck[index];
                newNode->next = currentColumn;
                currentColumn = newNode;
                cardAdded[index] = true;
            }
        }
        columns[i] = currentColumn;
    }
}

// Helper-function to print the deck
void printDeck(Card deck[]) {
    for (int i = 0; i < 52; i++) {
        printf("[%c%c] ", deck[i].rank, deck[i].suit);
    }
    printf("\n");
}

// Function to "split" a deck of cards after "split" amount of cards iterated through and interleave into shuffled deck
Card* split(Card deck[], int split) {
    // Allocate memory for the new shuffled deck
    Card* shuffledDeck = (Card*)malloc(52 * sizeof(Card));
    if (shuffledDeck == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Create piles dependent on the split and generate a random split-value if none is provided
    Card* pile1;
    Card* pile2;

    if (split > 0 && split < 52) {
        pile1 = deck;
        pile2 = deck + split;
    } else {
        srand(time(NULL)); // Seed the random number generator
        split = rand() % 52; // Generate a random split
        pile1 = deck;
        pile2 = deck + split;
    }

    printf("Pile1\n");
    printDeck(pile1);
    printf("\n");

    printf("Pile2\n");
    printDeck(pile2);
    printf("\n");

    // Index variables for iterating through piles a card at a time
    int index1 = 0;
    int index2 = 0;
    int shuffledIndex = 0;

    // Interleave cards from the two piles into the shuffled deck
    while (index1 < split && index2 < 52 - split) {
        shuffledDeck[shuffledIndex++] = pile1[index1++];
        shuffledDeck[shuffledIndex++] = pile2[index2++];
    }

    // If there are remaining cards in pile1 or pile2, we add them to the shuffled deck
    while (index1 < split) {
        shuffledDeck[shuffledIndex++] = pile1[index1++];
    }

    while (index2 < 52 - split) {
        shuffledDeck[shuffledIndex++] = pile2[index2++];
    }

    return shuffledDeck;
}

// Function to shuffle a deck using the Fisher-Yates shuffling-algorithm
void shuffleDeck(Card deck[]) {
    //Initialize an int value to keep track of the number of cards in the deck
    int numCards = 50;

    // Initialize the shuffled deck
    Card shuffledDeck[numCards];

    // Initialize a random seed
    srand(time(NULL));

    // Integer to store the size of the unshuffled pile
    int unshuffledSize = numCards;

    // Loop to iterate through cards
    for (int i = 0; i < numCards; i++) {
        // Select a random index in the unshuffled pile
        int randomIndex = rand() % unshuffledSize;

        // The random index is attributed to a random card and moved to the shuffled deck
        shuffledDeck[i] = deck[randomIndex];

        // The selected card is then replaced with top card from the unshuffled pile
        deck[randomIndex] = deck[unshuffledSize - 1];

        // Decrement size of unshuffled pile
        unshuffledSize--;
    }

    // Update our deck to match the shuffled deck
    for (int i = 0; i < numCards; i++) {
        deck[i] = shuffledDeck[i];
    }
}





