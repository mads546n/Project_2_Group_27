#include "controller.h"
#include <stdio.h>
#include <string.h>
#include "../model/model.h"

bool playPhase = false;

void setPhasePlay(bool isPlayPhase) {
    playPhase = isPlayPhase;
    if (playPhase) {
        printf("Play phase has started.\n");
    } else {
        printf("Back to STARTUP phase.\n");
    }
}



void input(){
    char chr[256];
    scanf("%s", chr);
//    printf ("Length is: %zu \n",strlen(chr));
//    startDeck(chr);







}