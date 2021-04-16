#ifndef MVOEMENT_H
#define MOVEMENT_H

char getPlayerInput();
void movePlayer(char** map, int* row, int* col, char* direction, int* dimensions, char newDirection);
int checkBounds(int row, int col, int* dimensions, char** map);
int checkLimit(int row, int col, int limRow, int limCol);
int checkDirection(char direction);

#endif
