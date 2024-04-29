#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "view.h"

// Define maximum length for last command and message
#define MAX_COMMAND_LENGTH 100
#define MAX_MESSAGE_LENGTH 100

void displayBoard(Card columns[][7], bool areColumnsEmpty, char* message, char* lastCommand) {
    printf("Yukon Solitaire\n\n");

    // Display the columns
    printf("Columns:\n");
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    if (!areColumnsEmpty) {
        for (int i = 0; i < 7; i++) {
            if (columns[i][0].rank != '\0') {
                printf("[%c%c]\t", columns[i][0].rank, columns[i][0].suit);
            } else {
                printf("[]\t");
            }
        }
    } else {
        for (int i = 0; i < 7; i++) {
            printf("[]\t");
        }
    }
    printf("\n\n");

    // Display the foundations as empty
    printf("Foundations:\n");
    for (int i = 0; i < 4; i++) {
        printf("F%d []\n", i + 1);
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


