#include <stdio.h>
#include "view.h"

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

    printf("LAST command: %s\n", lastCommand);

    // Display message
    printf("Message: %s\n", message);

    // Input prompt
    printf("Input > ");
}
