#include "controller.h"
#include "view.h"
#include <string.h>
#include <stdlib.h>

// Function to process user commands
void handle_command(const char* command, CardList* deck) {
    if (strcmp(command, "shuffle") == 0) {
        shuffle_deck(deck);
        display_message("Deck shuffled.");
    } else if (strncmp(command, "load ", 5) == 0) {
        const char* filename = command + 5;
        load_deck_from_file(deck, filename);
        display_message("Deck loaded from file.");
    } else {
        display_message("Invalid command.");
    }
    display_deck(deck);
}
