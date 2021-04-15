#ifndef MAP_H
#define MAP_H

void updateMap(char** map, int* dimensions, int newRow, int newCol, char direction) ;
char** generateMap(int row, int col);
void freeMap(char** map, int col);

#endif
