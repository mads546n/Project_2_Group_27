#include <stdio.h>
#include "view.h"

void displayBoard(Column *columns[], bool areColumnsEmpty, char* message) {
    printf("Yukon Solitaire\n\n");

    // Display the columns
    printf("Columns:\n");
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");

    // Iterate over each row in the columns
    for (int row = 0; row < 13; row++) {
        bool isEmptyRow = true; // Flag to track if row is empty
        for (int col = 0; col < 7; col++) {
            // Print current card in the column and row
            if (columns[col]->top != NULL) {
                // Print the card if it exists
                printf("[%c%c]\t", columns[col]->top->suit, columns[col]->top->rank);
                isEmptyRow = false; // Now mark the row as "not empty"
                columns[col]->top = columns[col]->top->next;
            } else {
                printf("[]\t");
            }
        }
        // Print a new line if the row is NOT empty
        if (!isEmptyRow) {
            printf("\n");
        }
    }
    printf("\n");

    // Display the foundations as empty
    printf("Foundations:\n");
    for (int i = 0; i < 4; i++) {
        printf("F%d []\n", i + 1);
    }
    printf("\n");

    // Display message
    printf("Message: %s\n", message);

    // Input prompt
    printf("Input > ");
}
