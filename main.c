#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define MAX_RANK 13
#define MAX_SUIT 4
#define MAX_CARDS 52
#define MAX_COLUMNS 7
#define MAX_FOUNDATIONS 4

#define CLUBS 'C'
#define DIAMONDS 'D'
#define HEARTS 'H'
#define SPADES 'S'

#define ACE 1
#define JACK 11
#define QUEEN 12
#define KING 13

#define FOUNDATION 'F'
#define TABLEAU 'C'

typedef struct Card {
    int rank;
    char suit;
    struct Card* next;
} Card;

typedef struct {
    Card* top;
} Stack;

typedef struct {
    Stack foundations[MAX_FOUNDATIONS];
    Stack tableaus[MAX_COLUMNS];
    Stack stock;
} Game;

// Function prototypes
void initialize(Game* game);
void push(Stack* stack, int rank, char suit);
void print_card(Card* card);
void print_stack(Stack* stack);
void print_game(Game* game);
void load_deck(Game* game, char* filename);
void shuffle_deck(Game* game);
void deal_cards(Game* game);
bool is_valid_move(Card* from, Card* to);
bool move_card(Game* game, char* move);
void play_game(Game* game);

int main() {
    Game game;
    initialize(&game);

    // Load and shuffle the deck
    load_deck(&game, "deck.txt");
    shuffle_deck(&game);

    // Deal cards to the tableau
    deal_cards(&game);

    // Play the game
    play_game(&game);

    return 0;
}

void initialize(Game* game) {
    for (int i = 0; i < MAX_FOUNDATIONS; i++) {
        game->foundations[i].top = NULL;
    }
    for (int i = 0; i < MAX_COLUMNS; i++) {
        game->tableaus[i].top = NULL;
    }
    game->stock.top = NULL;
}

void push(Stack* stack, int rank, char suit) {
    Card* new_card = (Card*)malloc(sizeof(Card));
    if (new_card == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    new_card->rank = rank;
    new_card->suit = suit;
    new_card->next = stack->top;
    stack->top = new_card;
}

void print_card(Card* card) {
    if (card->suit == FOUNDATION) {
        printf("%c%d", card->suit, card->rank);
    } else {
        if (card->rank == 10) {
            printf("T%c", card->suit);
        } else if (card->rank == JACK) {
            printf("J%c", card->suit);
        } else if (card->rank == QUEEN) {
            printf("Q%c", card->suit);
        } else if (card->rank == KING) {
            printf("K%c", card->suit);
        } else {
            printf("%d%c", card->rank, card->suit);
        }
    }
}

void print_stack(Stack* stack) {
    Card* current = stack->top;
    while (current != NULL) {
        print_card(current);
        printf(" ");
        current = current->next;
    }
}

void print_game(Game* game) {
    printf("Foundations: ");
    for (int i = 0; i < MAX_FOUNDATIONS; i++) {
        printf("[");
        if (game->foundations[i].top != NULL) {
            print_card(game->foundations[i].top);
        }
        printf("] ");
    }
    printf("\n");

    printf("Tableaus:\n");
    for (int i = 0; i < MAX_COLUMNS; i++) {
        printf("Column %d: ", i + 1);
        print_stack(&(game->tableaus[i]));
        printf("\n");
    }

    printf("Stock: ");
    print_stack(&(game->stock));
    printf("\n");
}

void load_deck(Game* game, char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        exit(EXIT_FAILURE);
    }

    char rank;
    char suit;
    int count = 0;
    while (fscanf(file, "%c%c\n", &rank, &suit) != EOF) {
        push(&(game->stock), rank - '0', suit);
        count++;
    }

    if (count != MAX_CARDS) {
        printf("Error: Invalid number of cards in the file.\n");
        exit(EXIT_FAILURE);
    }

    fclose(file);
}

void shuffle_deck(Game* game) {
    srand(time(NULL));

    // Copy cards to an array for shuffling
    Card* cards[MAX_CARDS];
    Card* current = game->stock.top;
    for (int i = 0; i < MAX_CARDS; i++) {
        cards[i] = current;
        current = current->next;
        cards[i]->next = NULL; // Disconnect from the original stack
    }

    // Shuffle the array
    for (int i = MAX_CARDS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card* temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }

    // Reconstruct the stack
    for (int i = 0; i < MAX_CARDS; i++) {
        push(&(game->stock), cards[i]->rank, cards[i]->suit);
    }
}

void deal_cards(Game* game) {
    for (int i = 0; i < MAX_COLUMNS; i++) {
        for (int j = 0; j <= i; j++) {
            Card* card = game->stock.top;
            game->stock.top = card->next;
            card->next = NULL;
            if (j == i) {
                card->suit = FOUNDATION;
            }
            push(&(game->tableaus[i]), card->rank, card->suit);
        }
    }
}

bool is_valid_move(Card* from, Card* to) {
    if (from == NULL || to == NULL) {
        return false;
    }
    if (from->suit == FOUNDATION) {
        return false; // Cannot move from foundation
    }
    if (to->suit == FOUNDATION) {
        if (from->rank == to->rank + 1 && from->suit == to->suit) {
            return true; // Valid move to foundation
        }
        return false;
    }
    if (from->rank == to->rank - 1 && from->suit % 2 != to->suit % 2) {
        return true; // Valid move to tableau
    }
    return false;
}

bool move_card(Game* game, char* move) {
    int from_col, to_col;
    char from_card[4], to_card[4];

    if (sscanf(move, "C%d:%3s->C%d", &from_col, from_card, &to_col) != 3) {
        printf("Error: Invalid move format.\n");
        return false;
    }

    from_col--;
    to_col--;

    if (from_col < 0 || from_col >= MAX_COLUMNS || to_col < 0 || to_col >= MAX_COLUMNS) {
        printf("Error: Invalid column number.\n");
        return false;
    }

    if (from_card[0] == 'A' || from_card[0] == 'T' || from_card[0] == 'J' || from_card[0] == 'Q' || from_card[0] == 'K') {
        from_card[0] -= '0';
    }

    if (to_card[0] == 'A' || to_card[0] == 'T' || to_card[0] == 'J' || to_card[0] == 'Q' || to_card[0] == 'K') {
        to_card[0] -= '0';
    }

    Card* from;
    if (from_card[1] == '\0') {
        from = game->tableaus[from_col].top;
        if (from == NULL) {
            printf("Error: No card in the source column.\n");
            return false;
        }
    } else {
        from = game->tableaus[from_col].top;
        while (from != NULL && (from->rank != from_card[0] || from->suit != from_card[1])) {
            from = from->next;
        }
        if (from == NULL) {
            printf("Error: Card not found in the source column.\n");
            return false;
        }
    }

    Card* to = game->tableaus[to_col].top;
    if (!is_valid_move(from, to)) {
        printf("Error: Invalid move.\n");
        return false;
    }

    // Move the card
    if (from->suit == FOUNDATION) {
        game->tableaus[to_col].top = from;
        game->tableaus[from_col].top = from->next;
        from->next = to;
    } else {
        Card* current = game->tableaus[from_col].top;
        while (current->next != from) {
            current = current->next;
        }
        current->next = from->next;
        from->next = to;
        game->tableaus[to_col].top = from;
    }

    return true;
}

void play_game(Game* game) {
    char move[10];
    while (true) {
        print_game(game);
        printf("Input move: ");
        fgets(move, sizeof(move), stdin);
        // Remove newline character if present
        size_t len = strlen(move);
        if (len > 0 && move[len - 1] == '\n') {
            move[len - 1] = '\0'; // Remove newline character
        }
        if (strcmp(move, "quit") == 0) {
            printf("Quitting the game.\n");
            break;
        }
        if (!move_card(game, move)) {
            printf("Invalid move. Try again.\n");
        }
    }
}

