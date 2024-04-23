#include <stdio.h>
#include "view/view.h"
#include "model/card.h"

int main() {
    // Sample game state
    Card columns[7][7]; // Initially empty columns

    char message[50] = "OK";

    bool isEmpty = true; // Flag to indicate if the game board is empty

    // Display the game board
    displayBoard(columns, isEmpty, message);

    return 0;
}