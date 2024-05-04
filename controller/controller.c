#include "controller.h"
#include "view.h"
#include "model.h"
#include <stdio.h>

bool playPhase = false;

void setPhasePlay(bool isPlayPhase) {
    playPhase = isPlayPhase;
    if (playPhase) {
        printf("Play phase has started.\n");
    } else {
        printf("Back to STARTUP phase.\n");
    }
}

void input() {
    char chr[256];
    scanf("%s", chr);
    // Additional logic based on input to interact with model and view
}
