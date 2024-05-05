#include "controller/controller.h"
#include "view/view.h"
#include <stdio.h>
#include "model/model.h"

int main() {
    GameState game = {0};
    char command[256];

    while (1) {
        printf("Input > ");
        fgets(command, sizeof(command), stdin);
        process_command(&game, command);
        display_game_state(&game);  // Always display the game state after processing a command
    }

    return 0;
}
