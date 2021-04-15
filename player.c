#include <stdio.h>
#include <stdlib.h>
#include "controller.h"
#include "boolean.h"
#include "player.h"
#include "direction.h"
#include "map.h"

void change_direction(char** map,int* x,int* y,char* direction,int* dimensions ,char new_direction) {
    if(new_direction == SHOOT) {

    }
    if(get_character(new_direction) == *direction) {
        int new_pos_x, new_pos_y;
        int d_x = 0;
        int d_y = 0;
        int* delta_x = &d_x;
        int* delta_y = &d_y;
        delta_player(delta_x,delta_y,new_direction);
        new_pos_x = *x + *delta_x;
        new_pos_y = *y + *delta_y;
        if(check_bounds(new_pos_x,new_pos_y,dimensions,map)) {
            update_map(map,dimensions,*x,*y,' ');
            update_position(map,x,y,new_pos_x,new_pos_y,dimensions);
            update_map(map,dimensions,new_pos_x,new_pos_y,get_character(new_direction));
        }
    }
    else {
        set_character_direction(direction,new_direction);
        update_map(map,dimensions,*x,*y,get_character(new_direction));
        update_position(map,x,y,*x,*y,dimensions);
    }
}

char get_character(char input) {
    char direction = ' ';
    if(input == WEST) {
        direction = '<';
    }
    else if (input == EAST){
        direction = '>';
    }
    else if(input == NORTH) {
        direction = '^';
    }
    else if(input == SOUTH) {
        direction = 'v';
    }
    return direction;
}

char get_character_direction(char input){
    char direction = ' ';
    if(input == '<') {
        direction = WEST;
    }
    else if (input == '>'){
        direction = EAST;
    }
    else if(input == '^') {
        direction = NORTH;
    }
    else if(input == 'v') {
        direction = SOUTH;
    }
    return direction;
}

void set_character_direction(char* character_direction,char input) {
    if(input == WEST) {
        *character_direction = '<';
    }
    else if (input == EAST){
        *character_direction = '>';
    }
    else if(input == NORTH) {
        *character_direction = '^';
    }
    else if(input == SOUTH) {
        *character_direction = 'v';
    }
}

void delta_player(int* delta_x, int* delta_y, char direction){
    if(direction == NORTH) {
        *delta_x = 0;
        *delta_y = -1;
    }
    else if(direction == SOUTH) {
        *delta_x = 0;
        *delta_y = 1;
    }
    else if(direction == WEST) {
        *delta_x = -1;
        *delta_y = 0;
    }
    else if(direction == EAST) {
        *delta_x = 1;
        *delta_y = 0;
    }
}

void update_position(char** map,int* x,int* y,int new_x,int new_y,int* dimensions) {
    if(check_bounds(new_x,new_y,dimensions,map)) {
        *x = new_x;
        *y = new_y;
    }
    else {
        printf("Out of bounds");
    }
}
