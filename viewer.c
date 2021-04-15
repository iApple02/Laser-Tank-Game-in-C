#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "viewer.h"
#include "movement.h"
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
    int i,numFrames, oldRow,oldCol,hitEnemy;
    int laserPosRow;
    int laserPosCol;
    int* delta_x = (int*)malloc(sizeof(int));
    int* delta_y = (int*)malloc(sizeof(int));
    char* laserDirection = (char*)malloc(sizeof(char));
    *laserDirection = '-';
    *delta_x = 0;
    *delta_y = 0;
    delta_x_y(delta_x,delta_y,direction,laserDirection);
    laserPosRow = *row + *delta_x;
    laserPosCol = *col + *delta_y;
    hitEnemy = FALSE;
    i = 0;
    oldRow = laserPosRow;
    oldCol = laserPosCol;
    numFrames = getNumFrames(dimensions,*delta_x,*delta_y,laserPosRow,laserPosCol);
    system("clear");

    /**Loop until the the frame rate count is met or we hit an enemy/player or we do not go over bounds check**/
    while(checkLimit(laserPosRow,laserPosCol,dimensions[0],dimensions[1]) && i <= numFrames && hitEnemy == FALSE) 
    {
        if(map[laserPosCol][laserPosRow] != opponent) 
        {
            updateMap(map, dimensions, laserPosRow, laserPosCol, *laserDirection);
            oldRow = laserPosRow;
            oldCol = laserPosCol;
            laserPosRow+= *delta_x;
            laserPosCol+= *delta_y;

        }
        /**When an enemy is hit, stop the game and mark the enemy position as X**/
        else if(map[laserPosCol][laserPosRow] == opponent)
        {
           hitEnemy = TRUE;
           updateMap(map, dimensions, laserPosRow, laserPosCol, 'X');
        }
        displayMap(map, dimensions[1],0);
        /**Update the old position to an empty character to remove bullet tracing**/
        updateMap(map, dimensions, oldRow, oldCol, ' ');
        i++;
        /**Delay the game by 0.15 second then show shooting animation**/
        newSleep(0.15);
        system("clear");
    }
    free(laserDirection);
    free(delta_x);
    free(delta_y);
    return hitEnemy;
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

void displayCommands() 
{
    printf("w to go/face up\n");
    printf("s to go/face down\n");
    printf("a to go/face left\n");
    printf("d to go/face right\n");
    printf("f to shoot laser\n");
}

void displayMap(char** map,int size_y,int mode) 
{
    int i;
    char* wall = (char*)malloc(sizeof(char) * (size_y + 2));

    memset(wall,'*',strlen(map[0])+ 2);
    printf("%s\n",wall);
    for(i=0;i<size_y;i++) 
    {
        printf("*");
        printColours(map[i], mode);
        printf("*");
        printf("\n");
    }
    printf("%s\n",wall);
    free(wall);
}

/** Prints strings in color by the integer mode, prints whole string if mode=1 otherwise
    print each character and check if it is a bullet which will be printed on a different character**/
void printColours(char* line,int mode) 
{
    int i;
    static int switchColours = 1;
    char* color = (char*)malloc(sizeof(char) * STRING_SIZE);
    if (mode == 1) 
    {
        printf("%s",line);
    }
    else {
        for(i=0;i<strlen(line);i++) 
        {
            if(hasBullet(line[i])) 
            {
                if(switchColours == 1) 
                {
                    PRINTCOLOR(line[i],RED);
                    switchColours = 0;
                }
                else 
                {
                    PRINTCOLOR(line[i],BLUE);
                    switchColours = 1;
                }
            }
            else 
            {
                printf("%c", line[i]);
            }
        }
    }
    free(color);
}

int has_bullet(char pos) 
{
    return (pos == '-' || pos == '|');
}


/** Evaluates the change of row & col and laser direction
    when animating the shooting sequence**/
void delta_x_y(int* delta_x, int* delta_y, char direction,char* laserDirection){
    char characterDirection = getCharacterDirection(direction);
    if(characterDirection == SHOOT) 
    {
        *delta_x = 0;
        *delta_y = 0;
        *laserDirection = ' ';
    }
    else if(characterDirection == NORTH) 
    {
        *delta_x = 0;
        *delta_y = -1;
        *laserDirection = '|';
    }
    else if(characterDirection == SOUTH) 
    {
        *delta_x = 0;
        *delta_y = 1;
        *laserDirection = '|';
    }
    else if(characterDirection == WEST) 
    {
        *delta_x = -1;
        *delta_y = 0;
        *laserDirection = '-';
    }
    else if(characterDirection == EAST) 
    {
        *delta_x = 1;
        *delta_y = 0;
        *laserDirection = '-';
    }
}