#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movement.h"
#include "player.h"
#include "boolean.h"
#include "direction.h"

/*Input char and pass the value of command to process*/
char getPlayerInput() 
{
    char command = ' ';
    scanf(" %c", &command);
    return command;
}

void movePlayer(char** map, int* row, int* col, char* direction, int* dimensions, char newDirection)
{
    changeDirection(map, row, col, direction, dimensions, newDirection);
}

/*Check boundary for map array so player cannot go beyond the '*' walls*/
int checkBounds(int row, int col, int* dimensions, char** map)
{
    int bool = FALSE;
    if( (col >= 0 && col < dimensions[1]) && (row >= 0 && row < dimensions[0])) 
    {
        bool = TRUE;
    }
    return bool;
}

int checkLimit(int row, int col, int limRow, int limCol) 
{
    int bool = FALSE;
    if(row >= 0 && row < limRow && col >= 0 && col < limCol) 
    {
        bool = TRUE;
    }
    return bool;
}

/*Check current direction of player to pass into shooting function*/
int checkDirection(char direction)
{
    int bool = FALSE;
    if(direction == SHOOT)
    {
        /**Do nothing**/
    }
    else if(direction == WEST || direction == EAST || direction == NORTH || direction == SOUTH) 
    {
        bool = TRUE;
    }

    return bool;
}