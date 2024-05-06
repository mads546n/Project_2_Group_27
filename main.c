#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <intrin.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include<unistd.h>
#include <assert.h>

//Linked list structure.
struct Deck {
    char* card;
    struct Deck* next;
};

// Define maximum length for last startDeck and message
#define MAX_COMMAND_LENGTH 100
#define MAX_MESSAGE_LENGTH 100
#define MAX_CARD_LENGTH 3
#define MAX_FILENAME_LENGTH 100

typedef struct Card {
    char rank;
    char suit;
    struct ListNode* next; // Pointer to the next card in the linked list
} Card;

typedef struct ListNode {
    Card card;
    struct ListNode* next;
} ListNode;

typedef struct FoundationNode {
    Card card;
    struct FoundationNode* next;
} FoundationNode;

Card deck[52];
ListNode *columns[7] = {NULL};
FoundationNode *foundations[4] = {NULL};

bool playPhase = false;

bool playmode = false;

// Define placeholder functions for each startDeck
//bool isDuplicate(Card deck[], int size, Card card) {
//    for (int i = 0; i < size; i++) {
//        if (deck[i].rank == card.rank && deck[i].suit == card.suit) {
//            return true;
//        }
//    }
//    return false;
//}

char buffer[3][51];

void insertStart(struct Deck** head, char* card){
    //Allocates memory for the linked list using malloc.
    struct Deck* newNode
            = (struct Deck*)malloc(sizeof(struct Deck));
    // store the card in the new Deck
    newNode->card = card;
    // the next pointer of new Deck will be on current head
    newNode->next = *head;
    // the current head will the new Deck
    *head = newNode;
}

void insertEnd(struct Deck** head, char* card){
    struct Deck* newNode
            = (struct Deck*)malloc(sizeof(struct Deck));
//    printf("size of malloc is%llu",sizeof(struct Deck));

    // store the card in the new Deck
    newNode->card = card;
    // Since the node will be last its next will be NULL
    newNode->next = NULL;
    // in case this is the first node make the newNode as
    // the head of the LinkedList
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    // Create a pointer to iterate till the last node
    struct Deck* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    // make the next of the tail to the new Deck
    current->next = newNode;
}
void printList(struct Deck* head){
    struct Deck* current = head;
    while (current != NULL) {
        printf("%s", current->card);
        current = current->next;
    }
}


// Function to initialize a sample deck
void load(Card deck[], char* filename) {
    int i = 1;
    struct Deck* head = NULL;
    //Checks for LD startDeck.
    //Checks if the LD startDeck has a path name.
//    char *filename = "../model/cards.txt";
    FILE *fp = fopen(filename, "r");
    char ch[105];
    // Assigns the cards from the fget buffer into the array so they are saved and then assigns them to a linked list.
    bool first = true;
    while (fgets(ch, 105, fp) != NULL) {
        if (first) {
            strcpy(buffer[0], ch);
            insertStart(&head, buffer[0]);
            deck[0].suit = buffer[0][1];
            deck[0].rank = buffer[0][0];
            first = false;
        } else {
            strcpy(buffer[i], ch);
            deck[i].suit = buffer[i][1];
            deck[i].rank = buffer[i][0];
            insertEnd(&head, buffer[i++]);
        }
    }
    printf("\n");
}


void processLD(char* filename) {
    chdir("../");
    load(deck, filename);
}
void processSW() {
    printf("Placeholder function for SW startDeck\n");
}

void processSI(char* argument) {
    printf("Placeholder function for SI startDeck\n");
}

void processSR() {
    printf("Placeholder function for SR startDeck\n");
}

void processSD(char* argument) {
    printf("Placeholder function for SD startDeck\n");
}

void processP() {
    playPhase = true;

    printf("Playmode On\n");
}

void processQ() {
    printf("Placeholder function for Q startDeck\n");
}

void processU() {
    printf("Placeholder function for U startDeck\n");
}

void processR() {
    printf("Placeholder function for R startDeck\n");
}

void processS(char* argument) {
    printf("Placeholder function for S startDeck\n");
}

void processL(char* argument) {
    printf("Placeholder function for L startDeck\n");
}
void processQQ() {
    exit(0);
}


// Function to distribute a given card deck along the columns
void distributeDeckToColumns(Card deck[], ListNode* columns[]) {
    bool cardAdded[52] = { false };
    int index = 0;
    for (int i = 0; i < 7; i++) {
        ListNode* currentColumn = NULL;
        int cardsToAdd = (i == 0) ? 1 : i + 5; // Determine number of cards to be distributed in each column
        for (int j = 0; j < cardsToAdd && index < 52; j++) {
            while (index < 52 && cardAdded[index]) {
                index++;
            }
            if (index < 52) {
                ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
                if (newNode == NULL) {
                    fprintf(stderr,"Memory allocation failed\n");
                    while (currentColumn != NULL) {
                        ListNode* temp = currentColumn;
                        currentColumn = currentColumn->next;
                        free(temp);
                    }
                    return;
                }
                newNode->card = deck[index];
                newNode->next = currentColumn;
                currentColumn = newNode;
                cardAdded[index] = true;
            }
        }
        columns[i] = currentColumn;
    }
}

// Helper-function to print the deck
void printDeck(Card deck[]) {
    for (int i = 0; i < 52; i++) {
        printf("[%c%c] ", deck[i].rank, deck[i].suit);
    }
    printf("\n");
}

// Function to "split" a deck of cards after "split" amount of cards iterated through and interleave into shuffled deck
Card* split(Card deck[], int split) {
    // Allocate memory for the new shuffled deck
    Card* shuffledDeck = (Card*)malloc(52 * sizeof(Card));
    if (shuffledDeck == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Create piles dependent on the split and generate a random split-value if none is provided
    Card* pile1;
    Card* pile2;

    if (split > 0 && split < 52) {
        pile1 = deck;
        pile2 = deck + split;
    } else {
        srand(time(NULL)); // Seed the random number generator
        split = rand() % 52; // Generate a random split
        pile1 = deck;
        pile2 = deck + split;
    }

    printf("Pile1\n");
    printDeck(pile1);
    printf("\n");

    printf("Pile2\n");
    printDeck(pile2);
    printf("\n");

    // Index variables for iterating through piles a card at a time
    int index1 = 0;
    int index2 = 0;
    int shuffledIndex = 0;

    // Interleave cards from the two piles into the shuffled deck
    while (index1 < split && index2 < 52 - split) {
        shuffledDeck[shuffledIndex++] = pile1[index1++];
        shuffledDeck[shuffledIndex++] = pile2[index2++];
    }

    // If there are remaining cards in pile1 or pile2, we add them to the shuffled deck
    while (index1 < split) {
        shuffledDeck[shuffledIndex++] = pile1[index1++];
    }

    while (index2 < 52 - split) {
        shuffledDeck[shuffledIndex++] = pile2[index2++];
    }

    return shuffledDeck;
}

// Function to shuffle a deck using the Fisher-Yates shuffling-algorithm
void shuffleDeck(Card deck[]) {
    //Initialize an int value to keep track of the number of cards in the deck
    int numCards = 50;

    // Initialize the shuffled deck
    Card shuffledDeck[numCards];

    // Initialize a random seed
    srand(time(NULL));

    // Integer to store the size of the unshuffled pile
    int unshuffledSize = numCards;

    // Loop to iterate through cards
    for (int i = 0; i < numCards; i++) {
        // Select a random index in the unshuffled pile
        int randomIndex = rand() % unshuffledSize;

        // The random index is attributed to a random card and moved to the shuffled deck
        shuffledDeck[i] = deck[randomIndex];

        // The selected card is then replaced with top card from the unshuffled pile
        deck[randomIndex] = deck[unshuffledSize - 1];

        // Decrement size of unshuffled pile
        unshuffledSize--;
    }

    // Update our deck to match the shuffled deck
    for (int i = 0; i < numCards; i++) {
        deck[i] = shuffledDeck[i];
    }
}

// Function to validate a performed move in accordance with the rules of Solitaire
bool validateMove(char sourceType, int sourceIndex, char destinationType, int destinationIndex, ListNode* columns, FoundationNode* foundations[]) {
    // Validate a move based on the type of source and destination

    // From column to column
    if (sourceType == 'C' && destinationType == 'C') {
        if (sourceIndex < 0 || sourceIndex >= 7 || destinationIndex < 0 ||destinationIndex >= 7) {
            printf("Invalid source- or destination column index\n");
            return false;
        }

        // Implement rules for checking if card from the source column is able to be placed on top of the destination column
        return true; // Returns true as of now

        // from column to foundation
    } else if (sourceType == 'C' && destinationType == 'F') {
        if (sourceIndex < 0 || sourceIndex >= 7 || destinationIndex < 0 ||destinationIndex >= 4) {
            printf("Invalid source- or destination column/foundation index\n");
            return false;
        }

        // Implement rules here as well
        return true; // Returns true as of now

        // From foundation to column
    } else if (sourceType == 'F' && destinationType == 'C') {
        if (sourceIndex < 0 || sourceIndex >= 4 || destinationIndex < 0 ||destinationIndex >= 7) {
            printf("Invalid source foundation or destination column index\n");
            return false;
        }

        // Implement rules here too
        return true; // For now

        // If none of the rules are obeyed
    } else {
        // It's an invalid move
        printf("Invalid move: Not possible to move from %c%d to %c%d\n", sourceType, sourceIndex, destinationType, destinationIndex);
        return false;
    }
}

// function to perform move if move is deemed "valid"
bool performMove(char sourceType, int sourceIndex, char destinationType, int destinationIndex, ListNode* columns[], FoundationNode* foundations[]) {
    // Perform the attempted move if the move is valid according to the rules specified in validateMove
    if (validateMove(sourceType, sourceIndex, destinationType, destinationIndex, /*LOOK HERE IF POINTER FAILURE*/ *columns, foundations)) {

        // Get the card that we need to move from the source-location
        Card cardToMove;

        // If moving from a column
        if (sourceType == 'C') {
            ListNode* sourceColumn = columns[sourceIndex];

            // Catch if the source column is empty
            if (sourceColumn == NULL) {
                printf("Source column is empty\n");
                return false;
            }

            // If the column isn't empty then we must remove the card from the source column
            cardToMove = sourceColumn->card;
            columns[sourceIndex] = sourceColumn->next;

            // Free the allocated memory
            free(sourceColumn);

        // If moving from a foundation
        } else if (sourceType == 'F') {
            FoundationNode* sourceFoundation = foundations[sourceIndex];

            // Catch if source foundation is empty
            if (sourceFoundation == NULL) {
                printf("Source foundation is empty\n");
                return false;
            }

            // If the foundation isn't empty, then move the card
            cardToMove = sourceFoundation->card;
            foundations[sourceIndex] = sourceFoundation->next;

            // Free allocated memory
            free(sourceFoundation);
        }

        // Now we insert the card into the given destination

        // If destination is a column
        if (destinationType == 'C') {
            ListNode* newCardNode = (ListNode*)malloc(sizeof(ListNode));

            // Catch if memory allocation is unsuccessful
            if (newCardNode == NULL) {
                printf("Memory allocation failed\n");
                return false;
            }
            newCardNode->card = cardToMove;
            newCardNode->next = columns[destinationIndex];
            columns[destinationIndex] = newCardNode;

            // IF MEMORY ERROR LOOK HERE
            free(newCardNode);

        // If destination is a foundation
        } else if (destinationType == 'F') {
            FoundationNode* newCardNode = (FoundationNode*)malloc(sizeof(FoundationNode));

            // Catch if memory allocation is unsuccessful
            if (newCardNode == NULL) {
                printf("Memory allocation failed\n");
                return false;
            }
            newCardNode->card = cardToMove;
            newCardNode->next = foundations[destinationIndex];
            foundations[destinationIndex] = newCardNode;

            // IF MEMORY ERROR LOOK HERE
            free(newCardNode);
        }

        // If the move was successful
        printf("Moved card successfully from %c%d to %c%d\n", sourceType, sourceIndex, destinationType, destinationIndex);
        return true;

        // If move wasn't successful
    } else {
        printf("Move from %c%d to %c%d failed\n", sourceType, sourceIndex, destinationType, destinationIndex);
        return false;
    }
}

// Function to process a given command for moving cards
void processMoveCommand(char* command, ListNode* columns[], FoundationNode* foundations[]) {
    // First we parse the command after the format (column) : (cardToBeMoved) -> (destination)
    char sourceType, destinationType;
    int sourceIndex, destinationIndex;
    char cardRank, cardSuit;

    // If condition to check if command is of appropriate length and format
    if (sscanf(command, "%c%d:%c%c->%c%d", &sourceType, &sourceIndex, &cardRank, &cardSuit, &destinationType, &destinationIndex) != 6) {
        printf("Invalid command format\n");
        return;
    }

    // If the command-format is correct and of correct length
    Card cardToMove;
    cardToMove.rank = cardRank;
    cardToMove.suit = cardSuit;

    // Call to the performMove function
    if (!performMove(sourceType, sourceIndex, destinationType, destinationIndex, columns, foundations)) {

        // if the condition is true, then the move was not able to be performed
        printf("Move failed\n");
    }
}

void displayBoard(ListNode* columns[], FoundationNode* foundations[], bool areColumnsEmpty, char* message, char* lastCommand) {

    printf("Yukon Solitaire\n\n");

    printf("Columns:\n");
    for (int i = 0; i < 7; i++) {
        printf("C%d\t", i + 1);
    }
    printf("\n");

    // Calculate the max height of call columns
    int maxHeight = 0;
    for (int i = 0; i < 7; i++) {
        ListNode* current = columns[i];
        int height = 0;
        while (current != NULL) {
            height++;
            current = current->next;
        }
        if (height > maxHeight) {
            maxHeight = height;
        }
    }
    // Print cards in each column
    for (int row = 0; row < maxHeight; row++) {
        for (int col = 0; col < 7; col++) {
            ListNode* current = columns[col];
            int height = 0;
            // Skip rows until appropriate height is found
            while (current != NULL && height < row) {
                current = current->next;
                height++;
            }
            if (current != NULL) {
                printf("[%c%c]\t", current->card.rank, current->card.suit);
            } else {
                printf("\t");
            }
        }
        printf("\n");
    }

    printf("\n");

    // Additional newline
    printf("\n");

    // Display the foundations as empty
    printf("Foundations:\n");
    for (int i = 0; i < 4; i++) {
        FoundationNode* current = foundations[i];
        if (current == NULL) {
            printf("F%d []\n", i + 1); // Print an empty foundation, if it is empty
        } else {
            while (current != NULL) {
                printf("F%d [%c%c]\n", i + 1, current->card.rank, current->card.suit); // Print cards in foundation
                current = current->next;
            }
        }
    }

    printf("\n");

    // Display last startDeck
    printf("LAST startDeck: %s\n", lastCommand);

    // Display message
    printf("Message: %s\n", message);

    // Input prompt

    printf("Input >  ");

    // Handle input
    char input[MAX_COMMAND_LENGTH];
    fgets(input, sizeof(input), stdin);
    // Remove newline character from input
    input[strcspn(input, "\n")] = 0;

    // Update last startDeck with the input received
    strncpy(lastCommand, input, MAX_COMMAND_LENGTH);

    // Check if startDeck is valid and update message
    // For now, assume all commands are invalid
    strncpy(message, "Error: Command Not Found", MAX_MESSAGE_LENGTH);

    char command[MAX_COMMAND_LENGTH];
    char argument[MAX_COMMAND_LENGTH];
    sscanf(input, "%s %s", command, argument);

    if (!playmode) {
        if (strcmp(command, "LD") == 0 ||
            strcmp(command, "SW") == 0 ||
            strcmp(command, "SI") == 0 ||
            strcmp(command, "SR") == 0 ||
            strcmp(command, "SD") == 0 ||
            strcmp(command, "P") == 0 ||
            strcmp(command, "Q") == 0 ||
            strcmp(command, "U") == 0 ||
            strcmp(command, "R") == 0 ||
            strcmp(command, "S") == 0 ||
            strcmp(command, "L") == 0) {
            // If the input startDeck is valid, update the message
            strncpy(message, "Command Ok", MAX_MESSAGE_LENGTH);

            switch (command[0]) {
                case 'L':
                    if (command[1] == 'D')
                        processLD(argument);
                    else
                        processL(argument);
                    break;
                case 'S':
                    processS(argument);
                    break;
                case 'R':
                    processR();
                    break;
                case 'U':
                    processU();
                    break;
                case 'Q':
                    processQ();
                    break;
                case 'P':
                    processP();
                    playmode = true;
                    break;
                case 'I':
                    if (command[1] == 'I')
                        processSI(argument);
                    break;
                case 'W':
                    processSW();
                    break;
                default:
                    // Error: Command not found
                    strncpy(message, "Error: Command Not Found", MAX_MESSAGE_LENGTH);


            }
        }
    }
//printf("%d", strcmp(command, "F"));
//    printf("%d", strcmp(command, "C"));

    if (playmode&&(strncmp(command, "C", 1) == 0 || strncmp(command, "F", 1) == 0)){
        int test = 0;
        // If the input startDeck is valid, update the message
        switch (command[0]) {
            case 'C':
                test = command[1] - '0';
                if(test >=1 && test <=7 ){
                    strncpy(message, "Command Ok", MAX_MESSAGE_LENGTH);
                    //Call relevant method here.
                    processMoveCommand(command, columns, foundations);
                }
                break;
            case 'F':
                test = command[1] - '0';
                if(test >=1 && test <=4 ){
                    strncpy(message, "Command Ok", MAX_MESSAGE_LENGTH);
                    //Call relevant method here.
                    processMoveCommand(command, columns, foundations);
                }
                break;
            default:
                // Error: Command not found
                strncpy(message, "Error: Command Not Found", MAX_MESSAGE_LENGTH);


        }
    }



}

// Function to save
void saveDeckToFile(Card deck[], char* filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: Unable to open file for writing\n");
        return;
    }

    // For-loop to iterate through the deck, that we're trying to save, and write each card in the file
    for (int i = 0; i < 52; i++) {
        fprintf(fp, "%c%c\n", deck[i].rank, deck[i].suit);
    }

    fclose(fp);
}

int main() {
    // Initialize a deck


    load(deck, "../cards.txt");


    // Printing sample deck
    printf("Original deck:\n");
    printDeck(deck);
    printf("\n");

    // Arrays of pointer to the head of each column and foundation


    char message[50] = "";

    char lastCommand[50] = "";

    bool isEmpty = true; // Flag to indicate if the game board is empty

    printf("Shuffled deck: \n");
    shuffleDeck(deck);
    for (int i = 0; i < 52; i++) {
        printf("[%c%c] ", deck[i].rank, deck[i].suit);
    }
    printf("\n");
    printf("\n");

    saveDeckToFile(deck, "shuffled_deck.txt");

    Card loadedDeck[52];
    load(loadedDeck, "shuffled_deck.txt");

    bool decksMatch = true;
    for (int i = 0; i < 52; i++) {
        if (loadedDeck[i].rank != deck[i].rank || loadedDeck[i].suit != deck[i].suit) {
            decksMatch = false;
            break;
        }
    }

    if (decksMatch) {
        printf("Loaded deck matches shuffled deck\n");
    } else {
        printf("Loaded deck doesn't match shuffled deck\n");
    }

    while (1) {

        distributeDeckToColumns(deck, columns);

        // Display the game board
        displayBoard(columns, foundations, isEmpty, message, lastCommand);

        //Important
        *columns = NULL;
    }

}