// main.c
#include "controller.h"
#include <stdio.h>

int main() {
    char command[256];

    printf("Enter command: ");
    fgets(command, sizeof(command), stdin);
    processCommand(command);

    return 0;
}
