#ifndef MODEL_H
#define MODEL_H

typedef struct card {
    char rank;
    char suit;
    struct card* next;
} Card;

typedef struct {
    Card* top;
} Column;

typedef struct {
    Column columns[7]; // 7 columns for Yukon
    Card* foundations[4]; // 4 foundations
    int in_play; // Indicates if the game is in the PLAY phase
} GameState;

Card* create_card(char rank, char suit);
void add_card_to_column(GameState* game, int column_index, Card* card);
void load_deck(GameState* game, const char* filename);

#endif
