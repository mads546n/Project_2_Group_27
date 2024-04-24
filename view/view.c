#include <stdio.h>
#include "view.h"

void displayBoard(Card columns[][7], bool areColumnsEmpty, char* message) {
    printf("Yukon Solitaire\n\n");

    // Display the columns
    printf("Columns:\n");
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");

    // Iterate over each row in the columns
    for (int row = 0; row < 13; row++) {
        bool isEmptyRow = true; // Flag to track if row is empty
        for (int col = 0; col < 7; col++) {
            // Print current card in the column and row
            if (columns[col][row].rank != '\0') {
                // Print the card if it exists
                printf("[%c%c]\t", columns[col][row].rank, columns[col][row].suit);
                isEmptyRow = false; // Now mark the row as "not empty"
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

           /*if (!areColumnsEmpty) {
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
        }
    }*/

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
