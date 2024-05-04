#include "view.h"
#include <stdio.h>
#include "../model/model.h"

// Function to display the deck
void display_deck(const CardList* deck) {
    const Card* current = deck->head;
    printf("Current Deck:\n");
    while (current != NULL) {
        printf("%c%c ", current->rank, current->suit);
        current = current->next;
    }
    printf("\n");
}

// Function to display a message
void display_message(const char* message) {
    printf("%s\n", message);
}
