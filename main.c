#include <stdio.h>
#include "view/view.h"

int main() {
    // Sample game state
    Card columns[7][7]; // Initially empty columns

    char message[50] = "";

    char lastCommand[50] = "";

    bool isEmpty = true; // Flag to indicate if the game board is empty

    // Display the game board
    displayBoard(columns, isEmpty, message, lastCommand);

    return 0;
}
