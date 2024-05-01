// controller.c
#include "controller.h"
#include "view.h"
#include <string.h>
#include <stdlib.h>

void processCommand(const char* command) {
    char cmd[256], filename[256];
    if (sscanf(command, "%s %s", cmd, filename) == 2) {
        if (strcmp(cmd, "LD") == 0) {
            Node* deck = loadDeckFromFile(filename);
            if (deck != NULL) {
                displayMessage("Deck loaded successfully.");
                freeLinkedList(deck);
            } else {
                displayMessage("Failed to load deck.");
            }
        }
    } else {
        displayMessage("Invalid command format.");
    }
}
