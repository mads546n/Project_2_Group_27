#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "view.h"
#include "../model/model.h"


// Define maximum length for last startDeck and message
#define MAX_COMMAND_LENGTH 100
#define MAX_MESSAGE_LENGTH 100
#define MAX_CARD_LENGTH 3
#define MAX_FILENAME_LENGTH 100


// Define placeholder functions for each startDeck
bool isDuplicate(Card deck[], int size, Card card) {
    for (int i = 0; i < size; i++) {
        if (deck[i].rank == card.rank && deck[i].suit == card.suit) {
            return true;
        }
    }
    return false;
}

void processLD(char* filename) {

//Card deck[52];
    ListNode *columns[7] = {NULL};
//
//    initializeSampleDeck(deck,filename, columns);
//    printf("AAA\n");
    // Open the file for reading
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file '%s'\n", filename);
        return;
    }

    // Initialize an array to store the deck
    Card deck[52];
    int deckSize = 0;

    // Read cards from the file
    char cardStr[MAX_CARD_LENGTH];
    while (fgets(cardStr, MAX_CARD_LENGTH, file) != NULL) {
        // Extract rank and suit from the string
        Card card;
        card.rank = cardStr[0];
        card.suit = cardStr[1];

        // Check for duplicate cards
        if (isDuplicate(deck, deckSize, card)) {
            printf("Error: Duplicate card found in the deck\n");
            fclose(file);
            return;
        }

        // Add the card to the deck
        deck[deckSize++] = card;
    }

    // Close the file
    fclose(file);

    // Check if the deck has exactly 52 cards
    if (deckSize != 52) {
        printf("Error: The deck must contain exactly 52 cards\n");
        return;
    }
    distributeDeckToColumns(deck, columns);


//     Now you have a valid deck stored in the 'deck' array
//     You can proceed to store it in linked lists or use it as needed

}




void processSW() {
    printf("Placeholder function for SW startDeck\n");
}

void processSI(char* argument) {
    printf("Placeholder function for SI startDeck\n");
}

void processSR() {
    printf("Placeholder function for SR startDeck\n");
}

void processSD(char* argument) {
    printf("Placeholder function for SD startDeck\n");
}

void processP() {
    printf("Placeholder function for P startDeck\n");
}

void processQ() {
    printf("Placeholder function for Q startDeck\n");
}

void processU() {
    printf("Placeholder function for U startDeck\n");
}

void processR() {
    printf("Placeholder function for R startDeck\n");
}

void processS(char* argument) {
    printf("Placeholder function for S startDeck\n");
}

void processL(char* argument) {
    printf("Placeholder function for L startDeck\n");
}



void displayBoard(ListNode* columns[], FoundationNode* foundations[], bool areColumnsEmpty, char* message, char* lastCommand) {

    printf("Yukon Solitaire\n\n");

    printf("Columns:\n");
    for (int i = 0; i < 7; i++) {
        printf("C%d\t", i + 1);
    }
    printf("\n");

    // Calculate the max height of call columns
    int maxHeight = 0;
    for (int i = 0; i < 7; i++) {
        ListNode* current = columns[i];
        int height = 0;
        while (current != NULL) {
            height++;
            current = current->next;
        }
        if (height > maxHeight) {
            maxHeight = height;
        }
    }

    // Print cards in each column
    for (int row = 0; row < maxHeight; row++) {
        for (int col = 0; col < 7; col++) {
            ListNode* current = columns[col];
            int height = 0;
            // Skip rows until appropriate height is found
            while (current != NULL && height < row) {
                current = current->next;
                height++;
            }
            if (current != NULL) {
                printf("[%c%c]\t", current->card.rank, current->card.suit);
            } else {
                printf("\t");
            }
        }
        printf("\n");
    }

    printf("\n");

    // Additional newline
    printf("\n");

    // Display the foundations as empty
    printf("Foundations:\n");
    for (int i = 0; i < 4; i++) {
        FoundationNode* current = foundations[i];
        if (current == NULL) {
            printf("F%d []\n", i + 1); // Print an empty foundation, if it is empty
        } else {
            while (current != NULL) {
                printf("F%d [%c%c]\n", i + 1, current->card.rank, current->card.suit); // Print cards in foundation
                current = current->next;
            }
        }
    }

    printf("\n");

    // Display last startDeck
    printf("LAST startDeck: %s\n", lastCommand);

    // Display message
    printf("Message: %s\n", message);

    // Input prompt

    printf("Input >  ");

    // Handle input
    char input[MAX_COMMAND_LENGTH];
    fgets(input, sizeof(input), stdin);
    // Remove newline character from input
    input[strcspn(input, "\n")] = 0;

    // Update last startDeck with the input received
    strncpy(lastCommand, input, MAX_COMMAND_LENGTH);

    // Check if startDeck is valid and update message
    // For now, assume all commands are invalid
    strncpy(message, "Error: Command Not Found", MAX_MESSAGE_LENGTH);

    char command[MAX_COMMAND_LENGTH];
    char argument[MAX_COMMAND_LENGTH];
    sscanf(input, "%s %s", command, argument);

    if (strcmp(command, "LD") == 0 ||
        strcmp(command, "SW") == 0 ||
        strcmp(command, "SI") == 0 ||
        strcmp(command, "SR") == 0 ||
        strcmp(command, "SD") == 0 ||
        strcmp(command, "P") == 0 ||
        strcmp(command, "Q") == 0 ||
        strcmp(command, "U") == 0 ||
        strcmp(command, "R") == 0 ||
        strcmp(command, "S") == 0 ||
        strcmp(command, "L") == 0) {
        // If the input startDeck is valid, update the message
        strncpy(message, "Command Ok", MAX_MESSAGE_LENGTH);

        switch (command[0]) {
            case 'L':
                if (command[1] == 'D')
                    processLD(argument);
                else processL(argument);
                break;
            case 'S':
                processS(argument);
                break;
            case 'R':
                processR();
                break;
            case 'U':
                processU();
                break;
            case 'Q':
                processQ();
                break;
            case 'P':
                processP();
                break;
            case 'I':
                if (command[1] == 'I')
                    processSI(argument);
                break;
            case 'W':
                processSW();
                break;
            default:
                // Error: Command not found
                strncpy(message, "Error: Command Not Found", MAX_MESSAGE_LENGTH);


        }
    }

}




