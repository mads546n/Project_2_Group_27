#include <stdio.h>
#include "view.h"

void displayBoard(Card columns[][7], bool areColumnsEmpty, char* message) {
    printf("Yukon Solitaire\n\n");
    // change 29-04 peter - terminal output changed to resemble figure 3 "initial view"
    // Display the columns
    printf("Columns:\t\t\t\t\t\t\tFoundations:\n");
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7");
    printf("\n\t\t\t\t\t\t\t\t[] F1");
    printf("\n\t\t\t\t\t\t\t\t[] F2");
    printf("\n\t\t\t\t\t\t\t\t[] F3");
    printf("\n\t\t\t\t\t\t\t\t[] F4\n\n");

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

    // Display message
    printf("\n\nMessage: %s\n", message);

    // Input prompt
    printf("Input > ");


}
