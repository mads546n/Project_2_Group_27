#include <stdio.h>
#include "view/view.h"

int main() {
    // Sample game state

    // Arrays of pointer to the head of each column and foundation
    ListNode* columns[7] = {NULL};
    FoundationNode* foundations[4] = {NULL};

    char message[50] = "";

    char lastCommand[50] = "";

    bool isEmpty = true; // Flag to indicate if the game board is empty


    while (1) {

        // Display the game board
        displayBoard(columns, foundations, isEmpty, message, lastCommand);


    }

    return 0;



}
