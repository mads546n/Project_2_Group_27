#ifndef VIEW_H
#define VIEW_H

#include <stdbool.h>
#include "../model/card.h"

void displayBoard(Card columns[][7], bool areColumnsEmpty, char* message);

#endif /* VIEW_H */
