#include <stdio.h>
#include "view/view.h"
#include "model/model.h"
#include "controller/controller.h"
#include <stdbool.h>
#include <string.h>


int main() {
    Card deck[52];
    ListNode *columns[7] = {NULL};
    FoundationNode *foundations[4] = {NULL};
    char message[50] = "";
    char lastCommand[50] = "";
    bool gameStarted = false;

    initializeSampleDeck(deck);  // Consider this part of the LD command in startup phase

    char command[50];
    while (1) {
        displayBoard(columns, foundations, gameStarted, message, lastCommand);

        printf("Input > ");
        fgets(command, sizeof(command), stdin); // Read user command
        processCommand(command, &gameStarted, deck, columns, foundations, message);

        if (strncmp(command, "QQ", 2) == 0) {
            break; // Exit the loop and end the program
        }
    }

    return 0;
}
