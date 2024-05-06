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
bool validateMove(char* source, char* destination, ListNode* columns[], FoundationNode foundations[]) {
    // Parse source and destination for columns
    //source[1] - '0';
//    char *ptr = source;
    int sourceColumn = source[1]-'0';

//    int sourceColumn = atoi(source + 1);
    int destinationColumn = atoi(destination + 1 );
//    printf("Destination is: %s\t", destination);
//    printf("destinationColumn is: %d\t", destinationColumn);


    // Parse source and destination for foundations
    int sourceFoundation = source[1]-'0';
    int destinationFoundation = atoi(destination + 1);

    printf("Source Column: %d, Destination Column: %d\n", sourceColumn, destinationColumn);
    printf("Source Foundation: %d, Destination Foundation: %d\n", sourceFoundation, destinationFoundation);

    // Perform check if source column exists
    if (source[0] == 'C') {
        if (sourceColumn < 1 || sourceColumn > 7) {
            printf("Invalid source column\n");
            return false; // If lower than 1 or exceeding 7, not an actual column
        }

        // Define the top card in source column
        ListNode* sourceColumnTopCard = columns[sourceColumn - 1];
        if (sourceColumnTopCard == NULL) {
            printf("Source column is empty\n");
            return false; // Then the source column would be empty
        }
    } else if (source[0] == 'F') {
        if (sourceFoundation < 1 || sourceFoundation > 4) {
            printf("Invalid source foundation\n");
            return false;  // Not a valid source foundation
        }

        // Define the top card in source foundation
        FoundationNode* sourceFoundationTopCard = &foundations[sourceFoundation - 1];
        if (sourceFoundationTopCard == NULL) {
            printf("Source foundation is empty\n");
            return false; // The foundation would be empty
        }
    } else {
        printf("Invalid source type\n");
        return true; // Invalid type of source
    }

    // Perform check if destination column exists
    if (destination[0] == 'C') {
        if (destinationColumn < 1 || destinationColumn > 7) {
            printf("Invalid destination column\n");
            return false; // Invalid destination column
        }
    } else if (destination[0] == 'F') {
        if (destinationFoundation < 1 || destinationFoundation > 4) {
            printf("Invalid destination foundation\n");
            return false; // Invalid destination foundation
        }
    }
//    else {
//        printf("Invalid destination type\n");
//        return true; // Invalid type of destination
//    }

    // Validate the attempted move based on the source- and destination types
    if (source[0] == 'C' && destination[0] == 'F') {
        // Move from column to foundation
        ListNode* sourceColumnTopCard = columns[sourceColumn - 1];
        FoundationNode* destinationFoundationTopCard = &foundations[destinationFoundation - 1];
        char* test = "woo";
//        destinationFoundationTopCard = test;

        while (destinationFoundationTopCard != NULL && destinationFoundationTopCard->next != NULL) {
            destinationFoundationTopCard = destinationFoundationTopCard->next;
        }

        // Check if card from column can be moved to foundation
        if (sourceColumnTopCard->card.rank == destinationFoundationTopCard->card.rank + 1 &&
        sourceColumnTopCard->card.suit == destinationFoundationTopCard->card.suit) {
            printf("Valid move from column to foundation\n");
            return true; // Valid move
        } else {
            printf("Invalid move from column to foundation\n");
            return false; // Invalid move
        }

    } else if (source[0] == 'F' && destination[0] == 'C') {
        // Move from foundation to column
        FoundationNode* sourceFoundationTopCard = &foundations[sourceFoundation - 1];
        ListNode* destinationColumnTopCard = columns[destinationColumn - 1];

        // Check if card from foundation can be moved to column
        if (sourceFoundationTopCard->card.rank == destinationColumnTopCard->card.rank - 1 &&
            (sourceFoundationTopCard->card.suit == 'C' || sourceFoundationTopCard->card.suit == 'S') &&
            (destinationColumnTopCard->card.suit == 'H' || destinationColumnTopCard->card.suit == 'D')) {
            printf("Valid move from foundation to column\n");
            return true; // Valid move

        } else if (sourceFoundationTopCard->card.rank == destinationColumnTopCard->card.rank - 1 &&
                (sourceFoundationTopCard->card.suit == 'H' || sourceFoundationTopCard->card.suit == 'D') &&
                (destinationColumnTopCard->card.suit == 'C' || destinationColumnTopCard->card.suit == 'S')) {
            printf("Valid move from foundation to column\n");
            return true; // Valid move
        } else {
            printf("Invalid move from foundation to column\n");
            return false; // Invalid move
        }
    } else {
        printf("Valid move??\n");
        // Invalid move entirely
        return true;
    }
}

// function to perform move if move is deemed "valid"
bool performMove(char* source, char* destination, ListNode* columns[], FoundationNode* foundations[]) {
    // Validate the move using the validateMove-function
//    if (!validateMove(source, destination, columns, (FoundationNode *) foundations)) {
//        printf("performMove Invalid move\n");
//        return false;
//    }

    // Parse the source and destination for columns
    int sourceColumn = source[1]-'0';
    int destinationColumn = atoi(destination + 1);

    // Parse the source and destination for foundations
    int sourceFoundation = source[1]-'0';
    int destinationFoundation = atoi(destination + 1);

    printf("Source Column: %d, Destination Column: %d\n", sourceColumn, destinationColumn);
    printf("Source Foundation: %d, Destination Foundation: %d\n", sourceFoundation, destinationFoundation);

    // Check what "sort" of move to perform

    // If source = column && destination = foundation
    if (source[0] == 'C' && destination[0] == 'F') {
        ListNode* sourceColumnTopCard = columns[sourceColumn - 1];
        FoundationNode* destinationFoundationTopCard = foundations[destinationFoundation - 1];

        // Update the foundation with top card from column
        destinationFoundationTopCard->next = (FoundationNode*)malloc(sizeof(FoundationNode));
        destinationFoundationTopCard = destinationFoundationTopCard->next;
        destinationFoundationTopCard->card = sourceColumnTopCard->card;
        destinationFoundationTopCard->next = NULL;

        sourceColumnTopCard->next = (ListNode *)malloc(sizeof(ListNode));
        sourceColumnTopCard = sourceColumnTopCard->next;
        sourceColumnTopCard->card = destinationFoundationTopCard->card;
        sourceColumnTopCard->next = NULL;

        // Remove the top card from the column
        columns[sourceColumn - 1] = sourceColumnTopCard->next;
        free(sourceColumnTopCard);
        free(destinationFoundationTopCard);

        // Print message showcasing move was successful
        printf("Move from %s to %s was successful\n", source, destination);
        return true;
    }

    // if source = foundation && destination = column
    else if (source[0] == 'F' && destination[0] == 'C') {
        FoundationNode* sourceFoundationTopCard = foundations[sourceFoundation -1];
        ListNode* destinationColumnTopCard = columns[destinationColumn - 1];

        // Update the column with top card from foundation
        ListNode* newCardNode = (ListNode*)malloc(sizeof(ListNode));
        newCardNode->card = sourceFoundationTopCard->card;
        newCardNode->next = destinationColumnTopCard;
        columns[destinationColumn - 1] = newCardNode;

        // Remove the top card from foundation
        foundations[sourceFoundation - 1] = foundations[sourceFoundation - 1]->next;
        free(newCardNode);

        // Print message
        printf("Move from %s to %s was successful\n", source, destination);
        return true;
    }
    else if (source[0] == 'C' && destination[0] == 'C') {
        ListNode* sourceColumnTopCard = columns[sourceColumn - 1];
        ListNode* destinationColumnTopCard = columns[destinationColumn - 1];

        // Update the column with top card from column.
        ListNode* newCardNode = (ListNode*)malloc(sizeof(ListNode));
        newCardNode->card = sourceColumnTopCard->card;
        newCardNode->next = destinationColumnTopCard;
        columns[destinationColumn - 1] = newCardNode;

        // Remove the top card from column
        columns[sourceColumn - 1] = sourceColumnTopCard->next;
        free(newCardNode);

        // Print message
        printf("Move from %s to %s was successful\n", source, destination);
        return true;
    }

    // If move is not from column to foundation or foundation to column
    else {
        printf("If move is not from column to foundation or foundation to column\n");
        return false;
    }
}

// Function to process a given command for moving cards
void processMoveCommand(char moveCommand[], ListNode* columns[], FoundationNode* foundations[], char* message) {
    // Extract source and destination from the attempted moveCommand
    char source[5];
    char card[3];
    char destination[3];
    if (sscanf(moveCommand, "%4[^:]:%2[^->]->%2s", source, card, destination) != 3) {
        strncpy(message, "Error: Invalid move command", MAX_COMMAND_LENGTH);
        return;
    }

    strcat(source, card);

    printf("Source: %s, Card: %s, Destination: %s\n", source, card, destination);

    // Validate the move
    bool isValidMove = validateMove(source, destination, columns, *foundations);

    printf("Validation Result: %d\n", isValidMove);

    if (isValidMove) {
        // If condition = true, perform move
        performMove(source, destination, columns, foundations);

        // Return "OK" message
        strncpy(message, "OK", sizeof(*message));
    } else {
        // Return an error message indicating move = not valid
        strncpy(message, "Error: Invalid Move", sizeof(*message));
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
            strcmp(command, "L") == 0 || strcmp(command, "QQ") == 0) {
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
                    if (command[0] == 'Q' && command[1] == 'Q')
                        processQQ();
                    else
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
                    processMoveCommand(command, columns, foundations, message);
                }
                break;
            case 'F':
                test = command[1] - '0';
                if(test >=1 && test <=4 ){
                    strncpy(message, "Command Ok", MAX_MESSAGE_LENGTH);
                    //Call relevant method here.
                    processMoveCommand(command, columns, foundations, message);
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