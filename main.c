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

// Define the Card struct
typedef struct Card {
    int rank;
    char suit;
    struct Card* next;
    bool face_up;
} Card;

// Define the Stack struct
typedef struct {
    Card* top;
} Stack;

// Define Foundation as an alias for Stack
typedef Stack Foundation;

// Define the Game struct
typedef struct {
    Stack foundations[MAX_FOUNDATIONS];
    Stack tableaus[MAX_COLUMNS];
    Stack stock;
    bool game_started;
} Game;

// Define the Move struct
typedef struct {
    char move_str[20];
    int from_col;
    int to_col;
    char from_card_desc[4];
} Move;

// Define the MoveHistory struct
typedef struct {
    Move moves[MAX_MOVES];
    int top;
} MoveHistory;

// Function prototypes
void initialize_game(Game* game);
void push(Stack* stack, Card* card);
Card* pop(Stack* stack);
void print_card(const Card* card);
void print_stack(const Stack* stack);
void print_card_in_column(const Stack* stack, int index);
int count_cards_in_column(const Stack* stack);
void print_game(const Game* game, const MoveHistory* history, const char* message, const char* last_command);
void load_deck(Game* game, const char* filename, char* message);
void shuffle_deck_random(Game* game, char* message);
void shuffle_deck_interleave(Game* game, int split, char* message);
void deal_cards(Game* game, char* message);
bool move_card(Game* game, MoveHistory* history, const char* move_str, char* message);
void display_deck(const Game* game, char* message);
void handle_command(Game* game, MoveHistory* history, const char* command, char* message, char* last_command);
void free_game(Game* game, char* message);
bool validate_move(const Card* from_card, const Card* to_card, char* message);
Card* find_card_in_stack(Stack* stack, const char* card_desc, char* message);
void add_move_to_history(MoveHistory* history, const Move* move, char* message);
void undo_move(Game* game, MoveHistory* history, char* message);
void redo_move(Game* game, MoveHistory* history, char* message);
void save_deck(const Game* game, const char* filename, char* message);
void quit_program(const Game* game, const MoveHistory* history, char* message);
void quit_game(const Game* game, const MoveHistory* history, char* message);

int main() {
    Game game;
    MoveHistory history;
    history.top = -1;
    initialize_game(&game);
    char message[100] = ""; // Define the message variable
    char last_command[100] = ""; // Define the last_command variable

    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    for (int i = 0; i < MAX_RANK; i++) {
        for (int j = 0; j < MAX_COLUMNS; j++) {
            printf("   \t");
        }
        if (i == 0) {
            printf("F1");
        } else if (i == 1) {
            printf("F2");
        } else if (i == 2) {
            printf("F3");
        } else if (i == 3) {
            printf("F4");
        }
        printf("\n");
    }
    printf("Last Command: %s\n", last_command);
    printf("Message: %s\n", message);
    printf("INPUT > ");

    char command[100];
    while (fgets(command, sizeof(command), stdin)) {
        command[strcspn(command, "\n")] = '\0';  // Remove newline character
        handle_command(&game, &history, command, message, last_command);
        print_game(&game, &history, message, last_command); // Pass message here
        printf("INPUT > ");
    }

    free_game(&game, message);
    return 0;
}

int count_cards_in_foundation(const Foundation* foundation) {
    int count = 0;
    Card* current_card = foundation->top;
    while (current_card != NULL) {
        count++;
        current_card = current_card->next;
    }
    return count;
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

void print_card_in_column(const Stack* stack, int index) {
    Card* current = stack->top;
    int count = 0;
    bool printed = false;
    while (current) {
        if (current->face_up) {
            if (count == index) {
                print_card(current);
                printed = true;
                break;
            }
            count++;
        } else {
            if (index == count_cards_in_column(stack) - 1) {
                printf("[ ] ");  // Print hidden card
                printed = true;
                break;
            }
        }
        current = current->next;
    }
    if (!printed) {
        printf("[ ] ");  // Print an empty card if no card was printed for this index
    }
}


int count_cards_in_column(const Stack* stack) {
    Card* current = stack->top;
    int count = 0;
    while (current) {
        if (current->face_up) {
            count++;
        }
        current = current->next;
    }
    return count;
}

void print_game(const Game* game, const MoveHistory* history, const char* message, const char* last_command) {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\tF1\tF2\tF3\tF4\n");
    for (int i = 0; i < MAX_RANK; i++) {
        for (int j = 0; j < MAX_COLUMNS + MAX_FOUNDATIONS; j++) {
            if (j < MAX_COLUMNS) {
                if (game->tableaus[j].top == NULL || i >= count_cards_in_column(&game->tableaus[j])) {
                    printf("   ");
                } else {
                    print_card_in_column(&game->tableaus[j], i);
                }
            } else {
                int foundation_index = j - MAX_COLUMNS;
                if (i == 0) {
                    if (game->foundations[foundation_index].top == NULL) {
                        printf("[] "); // Print empty foundation
                    } else {
                        print_card(game->foundations[foundation_index].top); // Print top card of foundation
                    }
                } else {
                    if (game->foundations[foundation_index].top != NULL && i < count_cards_in_foundation(&game->foundations[foundation_index])) {
                        printf("   "); // Leave space for the foundation if not on the first row
                    } else {
                        printf("[] "); // Print empty foundation
                    }
                }
            }
            printf("\t");
        }
        printf("\n");
    }
    printf("Last Command: %s\n", last_command);
    printf("Message: %s\n", message);
}


void load_deck(Game* game, const char* filename, char* message) {
    free_game(game, message);  // Clear existing game state
    FILE* file = fopen(filename, "r");
    if (!file) {
        strcpy(message, "Error: File not found.");
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
    strcpy(message, "Deck loaded.");

    // Initialize tableau columns with hidden cards
    for (int i = 0; i < MAX_COLUMNS; i++) {
        int hidden_cards = (i < 5) ? 10 : 9; // Determine the number of hidden cards based on column index
        for (int j = 0; j < hidden_cards; j++) {
            Card* hidden_card = (Card*)malloc(sizeof(Card));
            hidden_card->rank = -1; // Assigning a rank of -1 to represent a hidden card
            hidden_card->suit = ' ';
            hidden_card->face_up = false;
            push(&game->tableaus[i], hidden_card);
        }
    }
}

void shuffle_deck_random(Game* game, char* message) {
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
    strcpy(message, "Deck shuffled randomly.");
}

void shuffle_deck_interleave(Game* game, int split, char* message) {
    // Check for a valid split point
    if (split < 1 || split >= MAX_CARDS) {
        strcpy(message, "Invalid split value.");
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
    strcpy(message, "Deck shuffled interleave.");
}

void deal_cards(Game* game, char* message) {
    if (game->game_started) {
        strcpy(message, "Game already started.");
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
    strcpy(message, "Cards dealt.");
}

bool move_card(Game* game, MoveHistory* history, const char* move_str, char* message) {
    int from_col, to_col;
    char from_card_desc[4];
    if (sscanf(move_str, "%d %s %d", &from_col, from_card_desc, &to_col) != 3) {
        strcpy(message, "Invalid move format.");
        return false;
    }

    // Find the card in the source column
    Card* from_card = find_card_in_stack(&game->tableaus[from_col - 1], from_card_desc, message);
    if (!from_card) {
        return false;
    }

    // Check if destination column is within valid range
    if (to_col < 1 || to_col > MAX_COLUMNS) {
        strcpy(message, "Invalid destination column.");
        return false;
    }

    // Get the destination column top card
    Card* to_card = game->tableaus[to_col - 1].top;

    // Validate move
    if (!validate_move(from_card, to_card, message)) {
        return false;
    }

    // Perform the move (simplified)
    if (to_card == NULL || validate_move(from_card, to_card, message)) {
        pop(&game->tableaus[from_col - 1]);  // Remove card from source
        push(&game->tableaus[to_col - 1], from_card);  // Place card on destination

        // Record the move in history
        Move move;
        snprintf(move.move_str, sizeof(move.move_str), "%d %s %d", from_col, from_card_desc, to_col);
        add_move_to_history(history, &move, message);
        strcpy(message, "Move successful.");
        return true;
    }
    return false;
}

void display_deck(const Game* game, char* message) {
    print_stack(&game->stock);
    strcpy(message, "");

    // Display tableau columns
    for (int i = 0; i < MAX_COLUMNS; i++) {
        for (int j = 0; j < count_cards_in_column(&game->tableaus[i]); j++) {
            print_card_in_column(&game->tableaus[i], j);
            printf("\t");
        }
        printf("\n");
    }
}




void handle_command(Game* game, MoveHistory* history, const char* command, char* message, char* last_command) {
    strcpy(message, ""); // Reset message for each command
    strcpy(last_command, command); // Update last_command
    if (strncmp(command, "LD", 2) == 0) {
        const char* filename = command + 3;
        load_deck(game, filename, message);
    } else if (strcmp(command, "SW") == 0) {
        display_deck(game, message);
    } else if (strncmp(command, "SR", 2) == 0) {
        shuffle_deck_random(game, message);
    } else if (strncmp(command, "SI", 2) == 0) {
        int split;
        if (sscanf(command + 3, "%d", &split) == 1) {
            shuffle_deck_interleave(game, split, message);
        } else {
            strcpy(message, "Invalid shuffle interleave command format.");
        }
    } else if (strncmp(command, "SD", 2) == 0) {
        const char* filename = command + 3;
        save_deck(game, filename, message);
    } else if (strcmp(command, "P") == 0) {
        deal_cards(game, message);
    } else if (strncmp(command, "QQ", 2) == 0) {
        quit_program(game, history, message);
    } else if (strcmp(command, "Q") == 0) {
        quit_game(game, history, message);
    } else if (strncmp(command, "C", 1) == 0) {
        move_card(game, history, command, message);
    } else {
        strcpy(message, "Command not recognized. Please try again.");
    }
}

void free_game(Game* game, char* message) {
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
    strcpy(message, "Game freed.");
}

bool validate_move(const Card* from_card, const Card* to_card, char* message) {
    if (!from_card) {
        strcpy(message, "Card not found in source column.");
        return false;
    }
    if (to_card == NULL) return true;  // Allow moves to empty columns
    // Yukon rule: must be opposite color and one rank lower
    if ((from_card->suit == 'H' || from_card->suit == 'D') != (to_card->suit == 'H' || to_card->suit == 'D') &&
        from_card->rank == to_card->rank - 1) {
        return true;
    }
    strcpy(message, "Invalid move.");
    return false;
}

Card* find_card_in_stack(Stack* stack, const char* card_desc, char* message) {
    Card* current = stack->top;
    int rank;
    char suit;
    // Parse the card description to find rank and suit
    if (sscanf(card_desc, "%d%c", &rank, &suit) < 2) {
        // Handle error in card description
        strcpy(message, "Error in card description.");
        return NULL;
    }
    while (current) {
        if (current->rank == rank && current->suit == suit && current->face_up) {
            return current;
        }
        current = current->next;
    }
    strcpy(message, "Card not found.");
    return NULL;
}

void add_move_to_history(MoveHistory* history, const Move* move, char* message) {
    if (history->top < MAX_MOVES - 1) {
        history->top++;
        history->moves[history->top] = *move;
    } else {
        // Handle history overflow if necessary
        strcpy(message, "Move history is full. Oldest moves will not be recorded.");
    }
}

void undo_move(Game* game, MoveHistory* history, char* message) {
    if (history->top >= 0) {
        Move move = history->moves[history->top];
        history->top--;
        strcpy(message, "Undid move.");
        // Implement actual undo logic here, reversing the move
    } else {
        strcpy(message, "No more moves to undo.");
    }
}

void redo_move(Game* game, MoveHistory* history, char* message) {
    if (history->top < MAX_MOVES - 1 && history->moves[history->top + 1].from_col != 0) {
        history->top++;
        Move move = history->moves[history->top];
        strcpy(message, "Redid move.");
        // Implement actual redo logic here, re-applying the move
    } else {
        strcpy(message, "No more moves to redo.");
    }
}

void save_deck(const Game* game, const char* filename, char* message) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        strcpy(message, "Error: Could not save deck to file.");
        return;
    }

    // Traverse the stock stack and write each card to the file
    Card* current = game->stock.top;
    while (current) {
        fprintf(file, "%d %c\n", current->rank, current->suit);
        current = current->next;
    }

    fclose(file);
    strcpy(message, "Deck saved to file.");
}

void quit_program(const Game* game, const MoveHistory* history, char* message) {
    strcpy(message, "Quitting the program.");
    free_game(game, message);
    exit(0);
}

void quit_game(const Game* game, const MoveHistory* history, char* message) {
    strcpy(message, "Quitting the game.");
    free_game(game, message);
    exit(0);
}
