#ifndef PLAYER_H
#define PLAYER_H

void changeDirection(char** map, int* row, int* col, char* direction, int* dimensions, char newDirection);
char getCharacter(char input);
char getCharacterDirection(char input);
void setCharacterDirection(char* characterDirection, char input);
void changeCharacter(int* moveRow, int* moveCol, char direction);
void updatePosition(char** map, int* row, int* col, int newRow, int newCol, int* dimensions);

#endif
