#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "viewer.h"
#include "controller.h"
#include "newSleep.h"
#include "boolean.h"
#include "direction.h"
#include "player.h"
#include "map.h"



static int STRING_SIZE = 20;

void display_player_won() {
    printf("Congratulations, You Won!!!\n");
}


void display_player_lost() {
    printf("Congratulations, You lost dumbass!!!\n");
}
/**pointer integers x and y represent the player's position on the map**/
int shooting_animation(char** map,int* dimensions,int* x,int* y,char direction,char opponent) {
    int i,num_frames,old_x,old_y,hit_enemy;
    int laser_pos_x;
    int laser_pos_y;
    int* delta_x = (int*)malloc(sizeof(int));
    int* delta_y = (int*)malloc(sizeof(int));
    char* laser_direction = (char*)malloc(sizeof(char));
    *laser_direction = '-';
    *delta_x = 0;
    *delta_y = 0;
    delta_x_y(delta_x,delta_y,direction,laser_direction);
    laser_pos_x = *x + *delta_x;
    laser_pos_y = *y + *delta_y;
    hit_enemy = FALSE;
    i = 0;
    old_x = laser_pos_x;
    old_y = laser_pos_y;
    num_frames = get_num_frames(dimensions,*delta_x,*delta_y,laser_pos_x,laser_pos_y);
    system("clear");
    while(check_limit(laser_pos_x,laser_pos_y,dimensions[0],dimensions[1]) && i <= num_frames && hit_enemy == FALSE) {
        if(map[laser_pos_y][laser_pos_x] != opponent) {
            update_map(map,dimensions,laser_pos_x,laser_pos_y,*laser_direction);
            old_x = laser_pos_x;
            old_y = laser_pos_y;
            laser_pos_x+=*delta_x;
            laser_pos_y+=*delta_y;

        }
        else if(map[laser_pos_y][laser_pos_x] == opponent){
           hit_enemy = TRUE;
           update_map(map,dimensions,laser_pos_x,laser_pos_y,'X');
        }
        display_map(map,dimensions[1],0);
        update_map(map,dimensions,old_x,old_y,' ');
        i++;
        newSleep(2.0);
        system("clear");
    }
    free(laser_direction);
    free(delta_x);
    free(delta_y);
    return hit_enemy;
}

int get_num_frames(int* dimensions,int delta_x ,int delta_y,int x,int y) {
    int num_frames = 0;
    if(delta_y == 1 || delta_y == -1) {
        num_frames = delta_y > 0 ? (dimensions[1] - y) : y;
    }
    else if(delta_x == 1 || delta_x == -1){
        num_frames = delta_x > 0 ? dimensions[0] - x : x;
    }
    return num_frames;
}

void display_commands() {
    printf("w to go/face up\n");
    printf("s to go/face down\n");
    printf("a to go/face left\n");
    printf("d to go/face right\n");
    printf("f to shoot laser\n");
}

void display_map(char** map,int size_y,int mode) {
    int i;
    char* wall = (char*)malloc(sizeof(char) * (size_y + 2));

    memset(wall,'*',strlen(map[0])+ 2);
    printf("%s\n",wall);
    for(i=0;i<size_y;i++) {
        printf("*");
        print_colors(map[i], mode);
        printf("*");
        printf("\n");
    }
    printf("%s\n",wall);
    free(wall);
}

void print_colors(char* line,int mode) {
    int i;
    static int switch_colors = 1;
    char* color = (char*)malloc(sizeof(char) * STRING_SIZE);
    if (mode == 1) {
        printf("%s",line);
    }
    else {
        for(i=0;i<strlen(line);i++) {
            if(has_bullet(line[i])) {
                if(switch_colors == 1) {
                    PRINT_COLOR(line[i],RED);
                    switch_colors = 0;
                }
                else {
                    PRINT_COLOR(line[i],BLUE);
                    switch_colors = 1;
                }
            }
            else {
                printf("%c", line[i]);
            }
        }
    }
    free(color);
}

int has_bullet(char pos) {
    return (pos == '-' || pos == '|');
}

void delta_x_y(int* delta_x, int* delta_y, char direction,char* laser_direction){
    char character_direction = get_character_direction(direction);
    if(character_direction == SHOOT) {
        *delta_x = 0;
        *delta_y = 0;
        *laser_direction = ' ';
    }
    else if(character_direction == NORTH) {
        *delta_x = 0;
        *delta_y = -1;
        *laser_direction = '|';
    }
    else if(character_direction == SOUTH) {
        *delta_x = 0;
        *delta_y = 1;
        *laser_direction = '|';
    }
    else if(character_direction == WEST) {
        *delta_x = -1;
        *delta_y = 0;
        *laser_direction = '-';
    }
    else if(character_direction == EAST) {
        *delta_x = 1;
        *delta_y = 0;
        *laser_direction = '-';
    }
}
