#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "view.h"

// Define maximum length for last command and message
#define MAX_COMMAND_LENGTH 100
#define MAX_MESSAGE_LENGTH 100


// Define placeholder functions for each command
void processLD(char* argument) {
    printf("Placeholder function for LD command\n");
}

void processSW() {
    printf("Placeholder function for SW command\n");
}

void processSI(char* argument) {
    printf("Placeholder function for SI command\n");
}

void processSR() {
    printf("Placeholder function for SR command\n");
}

void processSD(char* argument) {
    printf("Placeholder function for SD command\n");
}

void processP() {
    printf("Placeholder function for P command\n");
}

void processQ() {
    printf("Placeholder function for Q command\n");
}

void processU() {
    printf("Placeholder function for U command\n");
}

void processR() {
    printf("Placeholder function for R command\n");
}

void processS(char* argument) {
    printf("Placeholder function for S command\n");
}

void processL(char* argument) {
    printf("Placeholder function for L command\n");
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
    for (int row = 0; row < 11; row++) {
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
                current = current->next;
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
        // If the input command is valid, update the message
        strncpy(message, "Command Ok", MAX_MESSAGE_LENGTH);

        switch (command[0]) {
            case 'L':
                processL(argument);
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
            case 'D':
                if (command[1] == 'L')
                    processLD(argument);
                else if (command[1] == 'D')
                    processSD(argument);
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




