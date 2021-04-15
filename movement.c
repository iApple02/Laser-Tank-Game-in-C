#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controller.h"
#include "player.h"
#include "boolean.h"
#include "direction.h"


char get_player_input() {
    char command = ' ';
    scanf(" %c",&command);
    return command;
}

void move_player(char** map,int* x,int* y,char* direction,int* dimensions,char new_direction) {
    change_direction(map,x,y,direction,dimensions,new_direction);
}

int check_bounds(int x,int y,int* dimensions,char** map){
    int bool = FALSE;
    if( (y >= 0 && y < dimensions[1]) &&
        (x >= 0 && x < dimensions[0])) {
        bool = TRUE;
    }
    return bool;
}

int check_limit(int x,int y,int lim_x,int lim_y) {
    int bool = FALSE;
    if(x >= 0 && x < lim_x && y >= 0 && y < lim_y) {
        bool = TRUE;
    }
    return bool;
}

int check_direction(char direction) {
    int bool = FALSE;
    if(direction == SHOOT) {
        /**Do nothing**/
    }
    else if(direction == WEST || direction == EAST || direction == NORTH || direction == SOUTH) {
        bool = TRUE;
    }

    return bool;
}
