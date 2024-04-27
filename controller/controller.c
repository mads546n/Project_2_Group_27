#include "controller.h"
#include <stdio.h>
#include <string.h>
#include "../model/model.h"
void input(){
    char chr[256];
    scanf("%s", chr);
    printf ("Length is: %zu \n",strlen(chr));
    command(chr);
}