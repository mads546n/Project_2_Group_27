#include "controller.h"
#include <stdio.h>
#include "../model/model.h"
#include <string.h>

void input(){
    char chr[256];
    scanf("%s", chr);
    printf ("Length is: %zu \n",strlen(chr));
    command(chr);
}