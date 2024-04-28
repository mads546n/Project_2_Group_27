#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "view.h"

// Define maximum length for last command and message
#define MAX_COMMAND_LENGTH 100
#define MAX_MESSAGE_LENGTH 100

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

    int columnSizes[7] = {1, 6, 7, 8, 9, 10, 11};

    // Print cards in each column
    for (int row = 0; row < 11; row++) {
        for (int col = 0; col < 7; col++) {
            ListNode* current = columns[col];
            int height = 0;
            // Skip rows until appropriate height is found
            while (current != NULL && height < row - (11 - columnSizes[col])) {
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

    // Display last command
    printf("LAST command: %s\n", lastCommand);

    // Display message
    printf("Message: %s\n", message);

    // Input prompt
    printf("Input >  ");

    // Handle input
    char input[MAX_COMMAND_LENGTH];
    fgets(input, sizeof(input), stdin);
    // Remove newline character from input
    input[strcspn(input, "\n")] = 0;

    // Update last command with the input received
    strncpy(lastCommand, input, MAX_COMMAND_LENGTH);

    // Check if command is valid and update message
    // For now, assume all commands are valid
    strncpy(message, "Command Ok", MAX_MESSAGE_LENGTH);
}
