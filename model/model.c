//
// Created by edvar on 21-04-2024.
//

#include <malloc.h>
#include <stdio.h>
#include <time.h>
#include "../view/view.h"

// Function to initialize a sample deck
void initializeSampleDeck(Card deck[]) {
    char suits[] = {'H', 'D', 'C', 'S'};
    char ranks[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    int index = 0;

    for (int s = 0; s < 4; s++) {
        for (int r = 0; r < 13; r++) {
            deck[index].suit = suits[s];
            deck[index].rank = ranks[r];
            index++;
        }
    }
    printf("\n");
}

// Function to distribute a given card deck along the columns
void distributeDeckToColumns(Card deck[], ListNode* columns[]) {
    int index = 0;
    for (int i = 0; i < 7; i++) {
        ListNode* currentColumn = NULL;
        for (int j = 0; j <= i; j++) {
            if (index < 52) { // Avoid accessing cards which are out of bounds
                ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
                if (newNode == NULL) {
                    fprintf(stderr,"Memory allocation failed\n");
                    return;
                }
                newNode->card = deck[index++];
                newNode->next = currentColumn;
                currentColumn = newNode;
            }
        }
        columns[i] = currentColumn;
    }

    // Free the allocated memory when done using it
    /*for (int i = 0; i < 7; i++) {
        ListNode* current = columns[i];
        while (current != NULL) {
            ListNode* temp = current;
            current = current->next;
            free(temp);
        }
    }*/
}

// Helper-function to print the deck
void printDeck(Card deck[]) {
    for (int i = 0; i < 52; i++) {
        printf("[%c%c] ", deck[i].rank, deck[i].suit);
    }
    printf("\n");
}

// Function to "split" a deck of cards after "x" amount of cards iterated through and interleave into shuffled deck
Card* split(Card deck[], int x) {
    // Allocate memory for the new deck
    Card* newDeck = (Card*)malloc(52 * sizeof(Card));
    if (newDeck == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Split the deck
    Card* pile1 = deck;
    Card* pile2 = deck + x;

    //Calculate size of each pile
    int sizePile1 = x;
    int sizePile2 = 52 - x;

    // Debug prints
    printf("Pile 1: \n");
    printDeck(pile1);
    printf("\n");

    printf("Pile 2: \n");
    printDeck(pile2);
    printf("\n");

    int index = 0;
    while (sizePile1 > 0 && sizePile2 > 0) {
        newDeck[index++] = *pile1++;
        newDeck[index++] = *pile2++;
        sizePile1--;
        sizePile2--;
    }

    // If remaining cards in pile1, add to new "shuffled deck"
    while (sizePile1 > 0) {
        newDeck[index++] = *pile1++;
        sizePile1--;
    }

    while (sizePile2 > 0) {
        newDeck[index++] = *pile2++;
        sizePile2--;
    }

    return newDeck;

    /*// Shuffle the cards from the two piles and combine into a new shuffled deck
    srand(time(NULL)); // Randomness definition
    int index = 0;
    while (index < 52) {
        // Interleave cards from the two piles into the shuffled deck
        if (pile1 < deck + x) {
            newDeck[index++] = *pile1++;
        }
        if (pile2 < deck + 52) {
            newDeck[index++] = *pile2++;
        }
    }

    return newDeck;*/
}