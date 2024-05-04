#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdbool.h>
#include "../model/model.h"

void setPhasePlay(bool isPlayPhase);
void input();
void distributeDeckToColumns();
void handle_command(const char* command, CardList* deck);

#endif //CONTROLLER_H
