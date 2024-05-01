#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX_RANK 13
#define MAX_COLUMNS 7
#define MAX_FOUNDATIONS 4
#define MAX_MOVES 100
#define MAX_CARDS 52 // Added for consistency

typedef struct Card {
    int rank;
    char suit;
    struct Card* next;
    bool face_up;
} Card;

typedef struct {
    Card* top;
} Stack;

typedef struct {
    Stack foundations[MAX_FOUNDATIONS];
    Stack tableaus[MAX_COLUMNS];
    Stack stock;
    bool game_started;
} Game;

typedef struct {
    char move_str[20];
    int from_col;
    int to_col;
    char from_card_desc[4];
} Move;

typedef struct {
    Move moves[MAX_MOVES];
    int top;
} MoveHistory;

// Function Prototypes
void initialize_game(Game* game);
void push(Stack* stack, Card* card);
Card* pop(Stack* stack);
void print_card(const Card* card);
void print_stack(const Stack* stack);
void print_game(const Game* game);
void load_deck(Game* game, const char* filename);
void shuffle_deck_random(Game* game);
void shuffle_deck_interleave(Game* game, int split);
void deal_cards(Game* game);
bool move_card(Game* game, MoveHistory* history, const char* move_str);
void display_deck(const Game* game);
void handle_command(Game* game, MoveHistory* history, const char* command);
void free_game(Game* game);
bool validate_move(const Card* from_card, const Card* to_card);
Card* find_card_in_stack(Stack* stack, const char* card_desc);
void undo_move(Game* game, MoveHistory* history);
void redo_move(Game* game, MoveHistory* history);
void add_move_to_history(MoveHistory* history, const Move* move);

int main() {
    Game game;
    MoveHistory history;
    history.top = -1;
    initialize_game(&game);

    char command[100];
    printf("Input > ");
    while (fgets(command, sizeof(command), stdin)) {
        command[strcspn(command, "\n")] = '\0';  // Remove newline character
        handle_command(&game, &history, command);
        printf("Last Command: %s\n", command);
        printf("Input > ");
    }

    free_game(&game);
    return 0;
}

void initialize_game(Game* game) {
    for (int i = 0; i < MAX_COLUMNS; i++) {
        game->tableaus[i].top = NULL;
    }
    for (int i = 0; i < MAX_FOUNDATIONS; i++) {
        game->foundations[i].top = NULL;
    }
    game->stock.top = NULL;
    game->game_started = false;
}

void push(Stack* stack, Card* card) {
    card->next = stack->top;
    stack->top = card;
}

Card* pop(Stack* stack) {
    if (stack->top == NULL) {
        return NULL;
    }
    Card* card = stack->top;
    stack->top = card->next;
    return card;
}

void print_card(const Card* card) {
    if (card == NULL || !card->face_up) {
        printf("[ ] ");
        return;
    }
    const char* rank_str = card->rank == 1 ? "A" :
                           card->rank == 10 ? "T" :
                           card->rank == 11 ? "J" :
                           card->rank == 12 ? "Q" :
                           card->rank == 13 ? "K" : "";
    if (card->rank >= 2 && card->rank <= 9) {
        printf("%d%c ", card->rank, card->suit);
    } else {
        printf("%s%c ", rank_str, card->suit);
    }
}

void print_stack(const Stack* stack) {
    Card* current = stack->top;
    while (current) {
        print_card(current);
        current = current->next;
    }
}

void print_game(const Game* game) {
    printf("Tableaus:\n");
    for (int i = 0; i < MAX_COLUMNS; i++) {
        printf("C%d: ", i + 1);
        print_stack(&game->tableaus[i]);
        printf("\n");
    }
    printf("Foundations:\n");
    for (int i = 0; i < MAX_FOUNDATIONS; i++) {
        printf("F%d: ", i + 1);
        print_stack(&game->foundations[i]);
        printf("\n");
    }
    printf("Stock: ");
    print_stack(&game->stock);
    printf("\n");
}

void load_deck(Game* game, const char* filename) {
    free_game(game);  // Clear existing game state
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: File not found.\n");
        return;
    }

    char line[10];
    while (fgets(line, sizeof(line), file)) {
        int rank;
        char suit;
        if (sscanf(line, "%d %c", &rank, &suit) == 2) {
            Card* new_card = (Card*)malloc(sizeof(Card));
            new_card->rank = rank;
            new_card->suit = suit;
            new_card->face_up = false;  // Cards are initially face down when loaded
            push(&game->stock, new_card);
        }
    }
    fclose(file);
    printf("Deck loaded.\n");
}

void shuffle_deck_random(Game* game) {
    int count = 0;
    Card* temp_stack[MAX_CARDS];
    Card* card = pop(&game->stock);
    while (card) {
        temp_stack[count++] = card;
        card = pop(&game->stock);
    }
    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        int j = rand() % (i + 1);
        Card* temp = temp_stack[i];
        temp_stack[i] = temp_stack[j];
        temp_stack[j] = temp;
    }
    for (int i = 0; i < count; i++) {
        push(&game->stock, temp_stack[i]);
    }
    printf("Deck shuffled randomly.\n");
}

void shuffle_deck_interleave(Game* game, int split) {
    // Check for a valid split point
    if (split < 1 || split >= MAX_CARDS) {
        printf("Invalid split value.\n");
        return;
    }

    Stack first_half, second_half;
    first_half.top = NULL;
    second_half.top = NULL;

    // Divide the deck into two halves
    for (int i = 0; i < split; i++) {
        push(&first_half, pop(&game->stock));
    }
    while (game->stock.top != NULL) {
        push(&second_half, pop(&game->stock));
    }

    // Interleave the two halves
    while (first_half.top != NULL || second_half.top != NULL) {
        if (first_half.top != NULL) {
            push(&game->stock, pop(&first_half));
        }
        if (second_half.top != NULL) {
            push(&game->stock, pop(&second_half));
        }
    }
}

void deal_cards(Game* game) {
    if (game->game_started) {
        printf("Game already started.\n");
        return;
    }
    for (int i = 0; i < MAX_COLUMNS; i++) {
        for (int j = 0; j <= i; j++) {
            Card* card = pop(&game->stock);
            if (card) {
                if (j == i) {
                    card->face_up = true;
                }
                push(&game->tableaus[i], card);
            }
        }
    }
    game->game_started = true;
}

bool move_card(Game* game, MoveHistory* history, const char* move_str) {
    int from_col, to_col;
    char from_card_desc[4];
    if (sscanf(move_str, "%d %s %d", &from_col, from_card_desc, &to_col) != 3) {
        printf("Invalid move format.\n");
        return false;
    }

    // Find the card in the source column
    Card* from_card = find_card_in_stack(&game->tableaus[from_col - 1], from_card_desc);
    if (!from_card) {
        printf("Card not found in source column.\n");
        return false;
    }

    // Check if destination column is within valid range
    if (to_col < 1 || to_col > MAX_COLUMNS) {
        printf("Invalid destination column.\n");
        return false;
    }

    // Get the destination column top card
    Card* to_card = game->tableaus[to_col - 1].top;

    // Validate move
    if (!validate_move(from_card, to_card)) {
        printf("Invalid move.\n");
        return false;
    }

    // Perform the move (simplified)
    if (to_card == NULL || validate_move(from_card, to_card)) {
        pop(&game->tableaus[from_col - 1]);  // Remove card from source
        push(&game->tableaus[to_col - 1], from_card);  // Place card on destination

        // Record the move in history
        Move move;
        snprintf(move.move_str, sizeof(move.move_str), "%d %s %d", from_col, from_card_desc, to_col);
        add_move_to_history(history, &move);
        return true;
    }
    return false;
}

void display_deck(const Game* game) {
    print_stack(&game->stock);
}

void handle_command(Game* game, MoveHistory* history, const char* command) {
    if (strncmp(command, "LD", 2) == 0) {
        const char* filename = command + 3;
        load_deck(game, filename);
    } else if (strcmp(command, "SW") == 0) {
        display_deck(game);
    } else if (strcmp(command, "P") == 0) {
        deal_cards(game);
    } else if (strcmp(command, "UNDO") == 0) {
        undo_move(game, history);
    } else if (strcmp(command, "REDO") == 0) {
        redo_move(game, history);
    } else if (strncmp(command, "MOVE", 4) == 0) {
        move_card(game, history, command + 5);  // Command is expected like "MOVE 1 A 2"
    } else {
        printf("Command not recognized.\n");
    }
}

void free_game(Game* game) {
    for (int i = 0; i < MAX_COLUMNS; i++) {
        while (game->tableaus[i].top) {
            Card* card = pop(&game->tableaus[i]);
            free(card);
        }
    }
    for (int i = 0; i < MAX_FOUNDATIONS; i++) {
        while (game->foundations[i].top) {
            Card* card = pop(&game->foundations[i]);
            free(card);
        }
    }
    while (game->stock.top) {
        Card* card = pop(&game->stock);
        free(card);
    }
}

bool validate_move(const Card* from_card, const Card* to_card) {
    if (!from_card) return false;
    if (to_card == NULL) return true;  // Allow moves to empty columns
    // Yukon rule: must be opposite color and one rank lower
    if ((from_card->suit == 'H' || from_card->suit == 'D') != (to_card->suit == 'H' || to_card->suit == 'D') &&
        from_card->rank == to_card->rank - 1) {
        return true;
    }
    return false;
}

Card* find_card_in_stack(Stack* stack, const char* card_desc) {
    Card* current = stack->top;
    int rank;
    char suit;
    // Parse the card description to find rank and suit
    if (sscanf(card_desc, "%d%c", &rank, &suit) < 2) {
        // Handle error in card description
        return NULL;
    }
    while (current) {
        if (current->rank == rank && current->suit == suit && current->face_up) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void add_move_to_history(MoveHistory* history, const Move* move) {
    if (history->top < MAX_MOVES - 1) {
        history->top++;
        history->moves[history->top] = *move;
    } else {
        // Handle history overflow if necessary
        printf("Move history is full. Oldest moves will not be recorded.\n");
    }
}

void undo_move(Game* game, MoveHistory* history) {
    if (history->top >= 0) {
        Move move = history->moves[history->top];
        history->top--;
        printf("Undid move: %s\n", move.move_str);
        // Implement actual undo logic here, reversing the move
    } else {
        printf("No more moves to undo.\n");
    }
}

void redo_move(Game* game, MoveHistory* history) {
    if (history->top < MAX_MOVES - 1 && history->moves[history->top + 1].from_col != 0) {
        history->top++;
        Move move = history->moves[history->top];
        printf("Redid move: %s\n", move.move_str);
        // Implement actual redo logic here, re-applying the move
    } else {
        printf("No more moves to redo.\n");
    }
}
