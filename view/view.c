#include "view.h"
#include <stdio.h>

void displayBoard(ListNode* columns[], FoundationNode* foundations[], const char* message, const char* lastCommand) {
    printf("\nYukon Solitaire - Current State\n");
    printf("Columns:\n");
    for (int i = 0; i < 7; i++) {
        printf("C%d\t", i + 1);
    }
    printf("\n");

    for (int row = 0; row < 11; row++) {
        for (int col = 0; col < 7; col++) {
            ListNode* current = columns[col];
            int height = 0;
            while (current != NULL && height < row) {
                current = current->next;
                height++;
            }
            if (current != NULL) {
                printf("%c%c\t", current->card.rank, current->card.suit);
            } else {
                printf("\t");
            }
        }
        printf("\n");
    }

    printf("Foundations:\n");
    for (int i = 0; i < 4; i++) {
        FoundationNode* current = foundations[i];
        if (current != NULL) {
            printf("F%d [%c%c]\n", i + 1, current->card.rank, current->card.suit);
        } else {
            printf("F%d [ ]\n", i + 1);
        }
    }

    printf("\nLast Command: %s\n", lastCommand);
    printf("Message: %s\n", message);
    printf("Input > ");
}
