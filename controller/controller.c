#include "controller.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool processInput(Card** deck, Card* columns[], char* message) {
    char input[256];
    printf("Input > ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline

    // Parse and execute commands
    return false;
}
