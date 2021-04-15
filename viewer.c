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


/*Initalise size of 20 for memory allocation when printing different colours*/
static int STRING_SIZE = 20;

/*Print win/lose statements*/
void displayPlayerWon() 
{
    printf("Congratulations, You Won!\n");
}
void displayPlayerLost() 
{
    printf("You Lost!!!\n");
}

/**pointer integers row and col represent the player's position on the map**/
int shootingAnimation(char** map, int* dimensions, int* row, int* col, char direction, char opponent) 
{
    int i,numFrames,old_x,old_y,hit_enemy;
    int laser_pos_x;
    int laser_pos_y;
    int* delta_x = (int*)malloc(sizeof(int));
    int* delta_y = (int*)malloc(sizeof(int));
    char* laserDirection = (char*)malloc(sizeof(char));
    *laserDirection = '-';
    *delta_x = 0;
    *delta_y = 0;
    delta_x_y(delta_x,delta_y,direction,laserDirection);
    laser_pos_x = *row + *delta_x;
    laser_pos_y = *col + *delta_y;
    hit_enemy = FALSE;
    i = 0;
    old_x = laser_pos_x;
    old_y = laser_pos_y;
    numFrames = get_numFrames(dimensions,*delta_x,*delta_y,laser_pos_x,laser_pos_y);
    system("clear");

    /**Loop until the the frame rate count is met or we hit an enemy/player or we do not go over bounds check**/
    while(check_limit(laser_pos_x,laser_pos_y,dimensions[0],dimensions[1]) && i <= numFrames && hit_enemy == FALSE) 
    {
        if(map[laser_pos_y][laser_pos_x] != opponent) 
        {
            update_map(map,dimensions,laser_pos_x,laser_pos_y,*laserDirection);
            old_x = laser_pos_x;
            old_y = laser_pos_y;
            laser_pos_x+=*delta_x;
            laser_pos_y+=*delta_y;

        }
        /**When an enemy is hit, stop the game and mark the enemy position as X**/
        else if(map[laser_pos_y][laser_pos_x] == opponent)
        {
           hit_enemy = TRUE;
           update_map(map,dimensions,laser_pos_x,laser_pos_y, 'X');
        }
        displayMap(map,dimensions[1],0);
        /**Update the old position to an empty character to remove bullet tracing**/
        updateMap(map,dimensions,old_x,old_y,' ');
        i++;
        /**Delay the game by 0.15 second then show shooting animation**/
        newSleep(0.15);
        system("clear");
    }
    free(laserDirection);
    free(delta_x);
    free(delta_y);
    return hit_enemy;
}

/** Returns the number of frames the shooting animation**/
int getNumFrames(int* dimensions,int delta_x ,int delta_y,int x,int y) 
{
    int numFrames = 0;
    if(delta_y == 1 || delta_y == -1) 
    {
        numFrames = delta_y > 0 ? (dimensions[1] - y) : y;
    }
    else if(delta_x == 1 || delta_x == -1)
    {
        numFrames = delta_x > 0 ? dimensions[0] - x : x;
    }
    return numFrames;
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

/** Prints strings in color by the integer mode, prints whole string if mode=1 otherwise
    print each character and check if it is a bullet which will be printed on a different character**/
void print_colors(char* line,int mode) {
    int i;
    static int switchColours = 1;
    char* color = (char*)malloc(sizeof(char) * STRING_SIZE);
    if (mode == 1) {
        printf("%s",line);
    }
    else {
        for(i=0;i<strlen(line);i++) {
            if(hasBullet(line[i])) {
                if(switchColours == 1) {
                    PRINTCOLOR(line[i],RED);
                    switchColours = 0;
                }
                else {
                    PRINTCOLOR(line[i],BLUE);
                    switchColours = 1;
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


/** Evaluates the change of row & col and laser direction
    when animating the shooting sequence**/
void delta_x_y(int* delta_x, int* delta_y, char direction,char* laserDirection){
    char character_direction = get_character_direction(direction);
    if(character_direction == SHOOT) {
        *delta_x = 0;
        *delta_y = 0;
        *laserDirection = ' ';
    }
    else if(character_direction == NORTH) {
        *delta_x = 0;
        *delta_y = -1;
        *laserDirection = '|';
    }
    else if(character_direction == SOUTH) {
        *delta_x = 0;
        *delta_y = 1;
        *laserDirection = '|';
    }
    else if(character_direction == WEST) {
        *delta_x = -1;
        *delta_y = 0;
        *laserDirection = '-';
    }
    else if(character_direction == EAST) {
        *delta_x = 1;
        *delta_y = 0;
        *laserDirection = '-';
    }
}