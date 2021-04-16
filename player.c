#include <stdio.h>
#include <stdlib.h>
#include "movement.h"
#include "boolean.h"
#include "player.h"
#include "direction.h"
#include "map.h"

/*Change player direction*/
void changeDirection(char** map, int* row, int* col, char* direction, int* dimensions, char newDirection) 
{
    if(newDirection == SHOOT) 
    {

    }
    /*Get direction of character and assign new direction for character.
    Function is used to switch direction of player*/
    if(getCharacter(newDirection) == *direction) 
    {
        int newPosRow, newPosCol;
        int directionRow = 0;
        int directionCol = 0;
        int* moveRow = &directionRow;
        int* moveCol = &directionCol;
        changeCharacter(moveRow,moveCol,newDirection);
        newPosRow = *row + *moveRow;
        newPosCol = *col + *moveCol;
        if(checkBounds(newPosRow,newPosCol,dimensions,map)) 
        {
            updateMap(map, dimensions,*row, *col,' ');
            updatePosition(map, row, col, newPosRow, newPosCol, dimensions);
            updateMap(map, dimensions, newPosRow, newPosCol, getCharacter(newDirection));
        }
    }
    /*If direction = direction then move character*/
    else 
    {
        setCharacterDirection(direction,newDirection);
        updateMap(map, dimensions, *row, *col, getCharacter(newDirection));
        updatePosition(map, row, col, *row, *col, dimensions);
    }
}

/*Get direction of character from input*/
char getCharacter(char input) 
{
    char direction = ' ';
    if(input == WEST) 
    {
        direction = '<';
    }
    else if (input == EAST)
    {
        direction = '>';
    }
    else if(input == NORTH) 
    {
        direction = '^';
    }
    else if(input == SOUTH) 
    {
        direction = 'v';
    }
    return direction;
}

/*Get direction of character from input*/
char getCharacterDirection(char input)
{
    char direction = ' ';
    if(input == '<') 
    {
        direction = WEST;
    }
    else if (input == '>')
    {
        direction = EAST;
    }
    else if(input == '^') 
    {
        direction = NORTH;
    }
    else if(input == 'v') 
    {
        direction = SOUTH;
    }
    return direction;
}

/*Set location of character from input*/
void setCharacterDirection(char* characterDirection, char input)
{
    if(input == WEST) 
    {
        *characterDirection = '<';
    }
    else if (input == EAST)
    {
        *characterDirection = '>';
    }
    else if(input == NORTH) 
    {
        *characterDirection = '^';
    }
    else if(input == SOUTH) 
    {
        *characterDirection = 'v';
    }
}

/*Move player up,down,left,right based on x/y axis*/
void changeCharacter(int* moveRow, int* moveCol, char direction)
{
    if(direction == NORTH) 
    {
        *moveRow = 0;
        *moveCol = -1;
    }
    else if(direction == SOUTH) 
    {
        *moveRow = 0;
        *moveCol = 1;
    }
    else if(direction == WEST) 
    {
        *moveRow = -1;
        *moveCol = 0;
    }
    else if(direction == EAST) 
    {
        *moveRow = 1;
        *moveCol = 0;
    }
}

/*Update the position from old player position to new player position using pointer*/
void updatePosition(char** map, int* row, int* col, int newRow, int newCol, int* dimensions) 
{
    if(checkBounds(newRow, newCol, dimensions,map)) 
    {
        *row = newRow;
        *col = newCol;
    }
    else {
        printf("Out of bounds");
    }
}
