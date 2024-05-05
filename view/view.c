#include "view.h"
#include <stdio.h>

void display_game_state(const GameState* game) {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    int empty = 1;
    for (int i = 0; i < 7; i++) {
        Card* current = game->columns[i].top;
        if (current) {
            empty = 0;
            break;
        }
    }
    if (empty) {
        printf("No cards to display. Please load a deck.\n");
        return;
    }

    for (int i = 0; i < 7; i++) {
        Card* current = game->columns[i].top;
        printf("Column %d: ", i + 1);
        while (current) {
            printf("%c%c ", current->rank, current->suit);
            current = current->next;
        }
        printf("\n");
    }
}
