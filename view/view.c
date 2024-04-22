#include "view.h"
#include <stdio.h>
#include <stdbool.h>

void displayBoard(Card columns[][7], Card foundations[], bool isEmpty, char* message) {
    printf("Yukon Solitaire\n\n");

    // Display the columns
    printf("Columns:\n");
    printf("C1 C2 C3 C4 C5 C6 C7\n");
    if (!isEmpty) {
        for (int i = 0; i < 7; i++) {
            if (columns[i][0].rank != '\0') {
                printf("[%c%c] ", columns[i][0].rank, columns[i][0].suit);
            } else {
                printf("[ ] ");
            }
        }
    } else {
        for (int i = 0; i < 7; i++) {
            printf("[ ] ");
        }
    }
    printf("\n\n");

    // Display the foundations
    printf("Foundations:\n");
    for (int i = 0; i < 4; i++) {
        printf("F%d [%c%c]\n", i + 1, foundations[i].rank, foundations[i].suit);
    }
    printf("\n");

    // Display message
    printf("Message: %s\n", message);

    // Input prompt
    printf("Input > ");
}
