#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movement.h"
#include "map.h"

/*Dimensions [0] stores the 2D array for row & [1] stores the 2D array for the col*/

void updateMap(char** map, int* dimensions, int newRow, int newCol, char direction) 
{
    if(checkBounds(newRow, newCol ,dimensions, map)) 
    {
        map[newCol][newRow] = direction;
    }
}


/*Initalise 2D Array and passed as map into another function*/
char** generateMap(int row, int col) 
{
    int i;
    char** map = (char**)malloc(sizeof(char*) * col);
    for(i=0;i<col;i++) 
    {
        char* line = (char*)malloc(sizeof(char)* row);
        memset(line,' ',row);
        map[i] = line;
    }
    return map;
}

/*Free map to prevent memeory leaks*/
void freeMap(char** map, int col) 
{
    int i;
    for(i=0; i<col; i++)
    {
        free(map[i]);
    }
    free(map);
}
