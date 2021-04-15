#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controller.h"
#include "map.h"

void updateMap(char** map, int* dimensions, int newRow, int newCol, char direction) 
{
    if(checkBounds(newRow, newCol ,dimensions, map)) 
    {
        map[newCol][newRow] = direction;
    }
}

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

void freeMap(char** map, int col) 
{
    int i;
    for(i=0; i<col; i++)
    {
        free(map[i]);
    }
    free(map);
}
