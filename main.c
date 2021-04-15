#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "viewer.h"
#include "boolean.h"
#include "controller.h"
#include "player.h"
#include "direction.h"
#include "newSleep.h"

const char UP = 'U';
const char DOWN = 'D';
const char LEFT = 'L';
const char RIGHT = 'R';

void game_func(char**,int*,int*,char*,int*,int*,char);
int process_action(char**,int*,int*,int*,char*,int*,char);
int playerOnEnemy(char,int,int,int,int);
static int checkDir(char);
static char translateDir(char);

int main(int argc, char** argv) 
{
    char* playerDirection;
    int* dimensions;
    char** map;
    /*Pointer to player x and y position in the game map*/
    int* player_x;
    int* player_y;
    int* enemyPos;
    int pRow, pCol;
    int eRow, eCol;
    int row, col;
    char playerDirection, enemyDirection;
    /** Evaluate command line arguments and convert to game values
        such as map width/height and player positioning etc...**/
    if(argc == 9) 
    {
        row = atoi(argv[1]);
        col = atoi(argv[2]);
        pRow = atoi(argv[3]);
        pCol = atoi(argv[4]);
        eRow = atoi(argv[6]);
        eCol = atoi(argv[7]);
        playerDirection = argv[5][0];
        enemyDirection = argv[8][0];
        /*Check ASCII value for lower case input*/
        playerDirection = playerDirection >=97 && playerDirection <= 122 ? playerDirection - 32 : playerDirection; 
        enemyDirection = enemyDirection >= 97 && enemyDirection <= 122 ? enemyDirection - 32 : enemyDirection;
    /** Check if the command line arguments are valid and
        width/height are within the range of valid vaues**/
    if( (pRow != eRow && pCol != eCol) &&
        (row >= 5 && col >= 5) &&
        (row <= 25 && col <= 25) &&
        checkDir(playerDirection) && checkDir(enemyDirection) &&
        check_limit(pRow, pCol, row, col) &&
        check_limit(eRow, eCol, row, col)) 
        {
            /**ALlocate memory for map, player's row and col positions and enemy information**/
            playerDirection = (char*)malloc(sizeof(char));
            dimensions = (int*)malloc(sizeof(int) * 2);
            enemyPos = (int*)malloc(sizeof(int) * 2);
            enemyPos[0] = eRow;
            enemyPos[1] = eCol;
            dimensions[0] = row;
            dimensions[1] = col;
            player_x = &pRow;
            player_y = &pCol;
            /**turns command line value of the character to face of the character on the map **/
            *playerDirection = translateDir(playerDirection);
            map = generate_map(row, col);
            /**Place the player into the map at the beginning**/
            map[*player_y][*player_x] = *playerDirection;
            enemyDirection = translateDir(enemyDirection);
            /**Place the enemy into the map at the beginning**/
            update_map(map,dimensions,eRow,eCol,enemyDirection);
            game_func(map,player_x,player_y,playerDirection,dimensions,enemyPos, enemyDirection);
            free_map(map, col);
            free(dimensions);
            free(playerDirection);
            free(enemyPos);
        }
        else 
        {
            printf("Invalid settings provided\n");
        }
    }
    else 
    {
        printf("Usage: ./laserTank <row_size> <col_size> <player_row> <player_col> <player_direction> <enemy_row> <enemy_col> <enemy_direction>\n");
    }
    return 0;
}

/**Game function that starts the game**/
void gameStart(char** map,int* player_x,int* player_y,char* direction,int* dimensions,int* enemyPos,char enemy) 
{
    int gameWon = FALSE;
    int gameLoop = TRUE;
    displayMap(map,dimensions[1],0);
    while(gameLoop) 
    {
        displayCommands();
        gameWon = process_action(map,dimensions,player_x,player_y,direction,enemyPos,enemy);
        displayMap(map,dimensions[1],1);
        if(gameWon) 
        {
            gameLoop = FALSE;
        }
    }
}

/** Evaluates player's input to either move or shoot,
    calls shoot animation or update player position on player input**/
int processAction(char** map,int* dimensions,int* x,int* y, char* direction,int* enemyPos,char enemy) 
{
    int winCondition = FALSE;
    char command = getPlayerInput();
    int* eRow;
    int* eCol;
    command = (command >= 97 && command <= 122) ? command - 32 : command;
    newSleep(0.15);
    if( command == WEST || command == EAST || command == NORTH || command == SOUTH) 
    {
        eRow = &enemyPos[0];
        eCol = &enemyPos[1];
        move_player(map,x,y,direction,dimensions,command);
        if(playerOnEnemy(enemy,enemyPos[0],enemyPos[1],*x,*y)) 
        {
            winCondition = shootingAnimation(map,dimensions,eRow,eCol,enemy,*direction);
            if(winCondition == TRUE) 
            {
                displayPlayerLost();
            }
        }
    }
    else if(command == SHOOT) 
    {
       winCondition = shootingAnimation(map,dimensions,x,y,*direction,enemy);
       if(winCondition == TRUE) 
       {
            displayPlayerWon();
       }
    }
    else 
    {
        printf("Invalid command, try again.\n");
    }
    return winCondition;
}

/** After the player moves to another tile on the map, check if the enemy
    is facing the player**/
int playerOnEnemy(char enemyDirection, int eRow,int eCol, int pRow,int pCol) 
{
    int isFacing = FALSE;
    if(enemyDirection == '<') 
    {
        if(eCol == pCol && pRow < eRow) 
        {
            isFacing = TRUE;
        }
    }
    else if(enemyDirection == '>') 
    {
        if(eCol == pCol && pRow > eRow) 
        {
            isFacing = TRUE;
        }
    }
    else if(enemyDirection == 'v') 
    {
        if(eCol < pCol && pRow == eRow) 
        {
            isFacing = TRUE;
        }
    }
    else if(enemyDirection == '^') 
    {
        if(eCol > pCol && pRow == eRow) 
        {
            isFacing = TRUE;
        }
    }
    return isFacing;
}

/**Checks if player inputs are valid or not, returns boolean TRUE/FALSE**/
static int checkDir(char dir) 
{
    int bool = FALSE;
    if(dir == UP || dir == DOWN  || dir == LEFT || dir == RIGHT) 
    {
        bool = TRUE;
    }
    return bool;
}


/**returns characters of player/enemy back to commands**/
static char translateDir(char dir) 
{
    char direction = '<';
    if(dir == UP) {
        direction = '^';
    }
    else if(dir == DOWN) 
    {
        direction = 'v';
    }
    else if(dir == RIGHT) 
    {
        direction = '>';
    }
    else if(dir == LEFT) 
    {
        direction = '<';
    }
    return direction;
}
