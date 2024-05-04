#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_deck(CardList* deck) {
    deck->head = NULL;
    deck->size = 0;
}

void load_deck_from_file(CardList* deck, const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open the file");
        return;
    }

    init_deck(deck);  // Reinitialize the deck
    char line[10];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Remove newline character if present
        size_t len = strlen(line);
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        Card* newCard = (Card*)malloc(sizeof(Card));
        if (newCard == NULL) {
            perror("Memory allocation failed");
            fclose(file);
            return;
        }

        // Assign rank and suit from file
        newCard->rank = line[0];
        newCard->suit = line[1];
        newCard->next = deck->head;
        deck->head = newCard;  // Insert at the head for simplicity
        deck->size++;
    }

    fclose(file);
}

void shuffle_deck(CardList* deck) {
    if (deck->size < 2) return;  // No need to shuffle if the deck has 1 or no cards

    // Convert linked list to array for easier shuffling
    Card** array = malloc(deck->size * sizeof(Card*));
    Card* current = deck->head;
    int i;
    for (i = 0; i < deck->size; i++) {
        array[i] = current;
        current = current->next;
    }

    // Fisher-Yates shuffle
    for (i = deck->size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card* temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    // Re-link the shuffled array back to linked list
    for (i = 0; i < deck->size - 1; i++) {
        array[i]->next = array[i + 1];
    }
    array[deck->size - 1]->next = NULL;
    deck->head = array[0];

    free(array);
}

void randomShuffle(CardList* deck) {
    // Shuffle logic goes here
}

void free_deck(CardList* deck) {
    Card* current = deck->head;
    while (current != NULL) {
        Card* next = current->next;
        free(current);
        current = next;
    }
    deck->head = NULL;
    deck->size = 0;
}
