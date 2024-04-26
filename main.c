#include <stdio.h>
#include "view/view.h"
#include "model/card.h"

int main() {
    Card deck[52];
    initializeSampleDeck(deck);

    Column *columns[7];
    for (int i = 0; i < 7; i++) {
        columns[i] = createColumn();
    }

    distributeCards(deck, columns, 7);

    char message[50] = "OK";
    bool isEmpty = true;

    displayBoard(columns, isEmpty, message);

    for (int i = 0; i < 7; i++) {
        freeColumn(columns[i]);
    }

    return 0;
}