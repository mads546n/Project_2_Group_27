#include "model.h"
#include <stdlib.h>
#include <stdio.h>

Card* create_card(char rank, char suit) {
    Card* newCard = (Card*)malloc(sizeof(Card));
    if (newCard) {
        newCard->rank = rank;
        newCard->suit = suit;
        newCard->next = NULL;
    }
    return newCard;
}

void add_card_to_column(GameState* game, int column_index, Card* card) {
    if (!game || !card) return;
    Card** top = &game->columns[column_index].top;
    card->next = *top;
    *top = card;
}

void load_deck(GameState* game, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("File does not exist.\n");
        return;
    }
    char rank, suit;
    int count = 0;
    while (fscanf(file, "%c%c\n", &rank, &suit) == 2) {
        Card* card = create_card(rank, suit);
        add_card_to_column(game, count % 7, card);
        count++;
    }
    fclose(file);
    if (count != 52) {
        printf("Invalid deck configuration.\n");
    } else {
        printf("Deck loaded successfully.\n");
    }
}
