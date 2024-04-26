#include "model.h"
#include "../controller/controller.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../view/view.h"
#include <stdlib.h>


void command (const char* chr){
    if (strcmp(chr, "LD") == 0) {
        if (strlen(chr)==2){
            printf("works, woo");

            char *filename = "../model/cards.txt";
            FILE* fp = fopen(filename, "r");
            Card* head = malloc(sizeof(Card));
            char ch[163];
            while (fgets(ch, 163, fp) !=NULL){
                printf("Character is %s \n", ch);
            }
        }
    }
}