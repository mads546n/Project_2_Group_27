#include "controller.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void process_command(GameState* game, char* command) {
    char cmd[10], filename[100];
    if (sscanf(command, "%s", cmd) == 1) {
        if (strcmp(cmd, "LD") == 0 && sscanf(command, "LD %s", filename) == 1) {
            load_deck(game, filename);
            printf("Deck loaded successfully.\n");
        } else if (strcmp(cmd, "P") == 0 && !game->in_play) {
            game->in_play = 1;  // Transition to PLAY phase
            printf("Game started. You are now in the PLAY phase.\n");
        } else if (strcmp(cmd, "QQ") == 0) {
            printf("Exiting game.\n");
            exit(0);  // Quit the program
        } else {
            printf("Command not available in current phase.\n");
        }
    }
}
