//
// Created by edvar on 21-04-2024.
//

#include <malloc.h>
#include <stdio.h>
#include <time.h>
#include <intrin.h>
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

// Older iteration of split-function
/*Card* split(Card deck[], int x) {

    // Assure that x is within valid range
    if (x <= 1 || x >= 52) {
        fprintf(stderr, "Invalid value for x. X must be > 1 && > 52\n");
    }

    // Allocate memory for the new deck
    Card* newDeck = (Card*)malloc(52 * sizeof(Card));
    if (newDeck == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Allocate memory for each pile
    Card* pile1 = (Card*)malloc((52 * x) * sizeof(Card));
    if (pile1 == NULL) {
        fprintf(stderr, "Memory alloc failed");
        return NULL;
    }

    Card* pile2 = (Card*)malloc((52 * x) * sizeof(Card));
    if (pile2 == NULL) {
        fprintf(stderr, "Memory alloc failed");
        return NULL;
    }


    // Load cards into pile1
    for (int i = 0; i < x; i++) {
        pile1[i] = deck[i];
    }

    // Load cards into pile2
    for (int i = x; i < 52; i++) {
        pile2[i - x] = deck[i];
    }

    // Debug statements
    printf("Pile1\n");
    printDeck(pile1);
    printf("\n");

    printf("Pile2\n");
    printDeck(pile2);
    printf("\n");

    // Initialize shuffled deck
    Card* shuffledDeck[52];

    // Free allocated memory for each pile
    free(pile1);
    free(pile2);

    return NULL;
}*/