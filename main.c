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
#define MAX_MOVES 100 // Maximum number of moves to store in history

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

typedef struct {
    char move[10];
    int from_col;
    char from_card[4];
    int to_col;
} Move;

typedef struct {
    Move moves[MAX_MOVES];
    int top;
} MoveHistory;

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
bool move_card(Game* game, MoveHistory* history, char* move);
void play_game(Game* game);
void display_deck(Game* game);
void shuffle_deck_random(Game* game);
void save_deck(Game* game, char* filename);
void load_saved_game(Game* game, char* filename);
void undo_move(Game* game, MoveHistory* history);
void redo_move(Game* game, MoveHistory* history);
void add_to_history(MoveHistory* history, char* move);
void free_deck(Stack* stack); // New function to free memory allocated for cards

int main() {
    Game game;
    MoveHistory history;
    history.top = -1; // Initialize top of history stack to -1

    initialize(&game);

    // Load and shuffle the deck
    load_deck(&game, NULL); // Load a new, unshuffled deck
    shuffle_deck(&game);

    // Deal cards to the tableau
    deal_cards(&game);

    // Play the game
    play_game(&game);

    // Free memory allocated for the deck when exiting the program
    free_deck(&(game.stock));

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
    // Print the column headers
    printf("C1 C2 C3 C4 C5 C6 C7\n");

    // Print the tableaus
    for (int i = 0; i < MAX_COLUMNS; i++) {
        print_stack(&(game->tableaus[i]));
        printf(" ");
    }

    // Print the foundations
    for (int i = 0; i < MAX_FOUNDATIONS; i++) {
        printf("[");
        if (game->foundations[i].top != NULL) {
            print_card(game->foundations[i].top);
        }
        printf("] ");
    }

    printf("\n");

    // Print the last command and message
    printf("Last Command: \n");
    printf("Message: \n");
    printf("Input > ");
}

void load_deck(Game* game, char* filename) {
    if (filename != NULL) {
        printf("Error: Filename parameter not supported. Loading a new deck.\n");
    }

    // Clear the existing stock stack
    free_deck(&(game->stock));

    // Load a new unshuffled deck
    for (char suit = CLUBS; suit <= SPADES; suit++) {
        for (int rank = 1; rank <= MAX_RANK; rank++) {
            push(&(game->stock), rank, suit);
        }
    }

    printf("New deck loaded.\n");
}

void display_deck(Game* game) {
    printf("Current deck order:\n");
    print_stack(&(game->stock));
    printf("\n");
}

void shuffle_deck(Game* game) {
    shuffle_deck_random(game); // You can choose either shuffle method
    // shuffle_deck_interleave(game, -1); // Or this one
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
    if (from->rank == to->rank - 1) {
        if (from->suit == HEARTS || from->suit == DIAMONDS) {
            if (to->suit == CLUBS || to->suit == SPADES) {
                return true;
            }
        } else if (from->suit == CLUBS || from->suit == SPADES) {
            if (to->suit == HEARTS || to->suit == DIAMONDS) {
                return true;
            }
        }
    }
    return false;
}

bool move_card(Game* game, MoveHistory* history, char* move) {
    int from_col;
    char from_card[4];
    int to_col;
    sscanf(move, "%d %3s %d", &from_col, from_card, &to_col);
    from_col--; // Adjust to zero-based index
    to_col--;

    // Check if the columns are valid
    if (from_col < 0 || from_col >= MAX_COLUMNS || to_col < 0 || to_col >= MAX_COLUMNS) {
        printf("Invalid column numbers.\n");
        return false;
    }

    // Check if the source column is empty
    if (game->tableaus[from_col].top == NULL) {
        printf("Source column is empty.\n");
        return false;
    }

    // Find the source card
    Card* from_card_ptr = game->tableaus[from_col].top;
    while (from_card_ptr != NULL && strcmp(from_card, "") != 0) {
        char current_card[4];
        sprintf(current_card, "%d%c", from_card_ptr->rank, from_card_ptr->suit);
        if (strcmp(from_card, current_card) == 0) {
            break;
        }
        from_card_ptr = from_card_ptr->next;
    }

    if (from_card_ptr == NULL) {
        printf("Card not found in source column.\n");
        return false;
    }

    // Find the destination card
    Card* to_card_ptr = NULL;
    if (game->tableaus[to_col].top != NULL) {
        to_card_ptr = game->tableaus[to_col].top;
        while (to_card_ptr->next != NULL) {
            to_card_ptr = to_card_ptr->next;
        }
    }

    // Check if the move is valid
    if (!is_valid_move(from_card_ptr, to_card_ptr)) {
        printf("Invalid move.\n");
        return false;
    }

    // Move the card
    if (to_card_ptr == NULL) {
        // Destination column is empty, move the card directly
        game->tableaus[to_col].top = from_card_ptr;
    } else {
        // Append the card to the end of the destination column
        to_card_ptr->next = from_card_ptr;
    }
    // Update the source column
    if (from_card_ptr == game->tableaus[from_col].top) {
        game->tableaus[from_col].top = from_card_ptr->next;
    } else {
        Card* prev = game->tableaus[from_col].top;
        while (prev->next != from_card_ptr) {
            prev = prev->next;
        }
        prev->next = from_card_ptr->next;
    }
    from_card_ptr->next = NULL;

    // Add the move to the history
    add_to_history(history, move);

    return true;
}

void play_game(Game* game) {
    MoveHistory history;
    history.top = -1; // Initialize top of history stack to -1
    char input[100];

    while (true) {
        print_game(game);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove trailing newline character

        if (strcmp(input, "q") == 0 || strcmp(input, "quit") == 0) {
            break;
        } else if (strcmp(input, "h") == 0 || strcmp(input, "history") == 0) {
            // Print move history
            printf("Move history:\n");
            for (int i = 0; i <= history.top; i++) {
                printf("%s\n", history.moves[i].move);
            }
        } else if (strcmp(input, "u") == 0 || strcmp(input, "undo") == 0) {
            // Undo last move
            undo_move(game, &history);
        } else if (strcmp(input, "r") == 0 || strcmp(input, "redo") == 0) {
            // Redo last undone move
            redo_move(game, &history);
        } else if (strcmp(input, "s") == 0 || strcmp(input, "save") == 0) {
            // Save current game state
            char filename[100];
            printf("Enter filename to save: ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = '\0'; // Remove trailing newline character
            save_deck(game, filename);
        } else if (strcmp(input, "l") == 0 || strcmp(input, "load") == 0) {
            // Load saved game state
            char filename[100];
            printf("Enter filename to load: ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = '\0'; // Remove trailing newline character
            load_saved_game(game, filename);
        } else if (strcmp(input, "d") == 0 || strcmp(input, "deck") == 0) {
            // Display current deck order
            display_deck(game);
        } else {
            // Try to move cards
            if (!move_card(game, &history, input)) {
                printf("Invalid command. Please try again.\n");
            }
        }
    }
}

void shuffle_deck_random(Game* game) {
    Card* deck[MAX_CARDS];
    int count = 0;

    // Store pointers to cards in an array
    while (game->stock.top != NULL) {
        deck[count++] = game->stock.top;
        game->stock.top = game->stock.top->next;
    }

    // Shuffle the array
    srand(time(NULL));
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card* temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }

    // Reassemble the deck
    for (int i = 0; i < count; i++) {
        deck[i]->next = game->stock.top;
        game->stock.top = deck[i];
    }
}

void save_deck(Game* game, char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Save the deck
    Card* current = game->stock.top;
    while (current != NULL) {
        fprintf(fp, "%d %c\n", current->rank, current->suit);
        current = current->next;
    }

    fclose(fp);
    printf("Game saved to %s.\n", filename);
}

void free_deck(Stack* stack) {
    Card* current = stack->top;
    while (current != NULL) {
        Card* temp = current;
        current = current->next;
        free(temp);
    }
    stack->top = NULL; // Reset the top pointer to NULL after freeing all cards
}

void load_saved_game(Game* game, char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    // Clear the existing stock stack
    free_deck(&(game->stock));

    // Load the deck
    int rank;
    char suit;
    while (fscanf(fp, "%d %c\n", &rank, &suit) != EOF) {
        push(&(game->stock), rank, suit);
    }

    fclose(fp);
    printf("Game loaded from %s.\n", filename);
}

void undo_move(Game* game, MoveHistory* history) {
    if (history->top >= 0) {
        char* last_move = history->moves[history->top].move;
        char reverse_move[10];
        sscanf(last_move, "%d %s %d", &reverse_move[0], reverse_move + 1, &reverse_move[2]);
        reverse_move[0] = reverse_move[0] + reverse_move[2] - 1;
        reverse_move[2] = reverse_move[2] + reverse_move[0] - 1;
        move_card(game, history, reverse_move);
        history->top--;
    } else {
        printf("No moves to undo.\n");
    }
}

void redo_move(Game* game, MoveHistory* history) {
    if (history->top < MAX_MOVES - 1) {
        history->top++;
        move_card(game, history, history->moves[history->top].move);
    } else {
        printf("No moves to redo.\n");
    }
}

void add_to_history(MoveHistory* history, char* move) {
    if (history->top < MAX_MOVES - 1) {
        strcpy(history->moves[++history->top].move, move);
    } else {
        // Shift all moves up by one to make space for the new move
        for (int i = 0; i < MAX_MOVES - 1; i++) {
            strcpy(history->moves[i].move, history->moves[i + 1].move);
        }
        strcpy(history->moves[MAX_MOVES - 1].move, move);
    }
}
