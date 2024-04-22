#include "view/view.h"
#include <stdio.h>

int main() {
    // Sample game state
    Card columns[7][7]; // Initially empty columns
    Card foundations[4] = {{'A', 'C'}, {'A', 'D'}, {'A', 'H'}, {'A', 'S'}};

    char lastCommand[50] = "Sample Command";
    char message[50] = "OK";

    bool isEmpty = true; // Flag to indicate if the game board is empty

    // Display the game board
    displayBoard(columns, foundations, isEmpty, message);

    return 0;
}
