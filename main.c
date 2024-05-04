#include "controller/controller.h"
#include "view/view.h"
#include "model/model.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main() {
    CardList deck;
    init_deck(&deck);

    char command[256];
    while (1) {
        printf("Enter command: ");
        if (fgets(command, sizeof(command), stdin) == NULL)
            break;
        if (strcmp(command, "quit\n") == 0)
            break;
        handle_command(command, &deck);
    }

    free_deck(&deck);
    return 0;
}
