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
int is_player_on_enemy_direction(char,int,int,int,int);
static int check_dir(char);
static char translate_dir(char);
int main(int argc, char** argv) {
    char* player_direction;
    int* dimensions;
    char** map;
    /*Pointer to player x and y position in the game map*/
    int* player_x;
    int* player_y;
    int* enemy_pos;
    int p_x,p_y;
    int e_x, e_y;
    int size_x,size_y;
    char p_dir,e_dir;
    /** Evaluate command line arguments and convert to game values
        such as map width/height and player positioning etc...**/
    if(argc == 9) {
        size_x = atoi(argv[1]);
        size_y = atoi(argv[2]);
        p_x = atoi(argv[3]);
        p_y = atoi(argv[4]);
        e_x = atoi(argv[6]);
        e_y = atoi(argv[7]);
        p_dir = argv[5][0];
        e_dir = argv[8][0];
        p_dir = p_dir >=97 && p_dir <= 122 ? p_dir - 32 : p_dir;
        e_dir = e_dir >= 97 && e_dir <= 122 ? e_dir - 32 : e_dir;
    /** Check if the command line arguments are valid and
        width/height are within the range of valid vaues**/
    if( (p_x != e_x && p_y != e_y) &&
        (size_x >= 5 && size_y >= 5) &&
        (size_x <= 25 && size_y <= 25) &&
        check_dir(p_dir) && check_dir(e_dir) &&
        check_limit(p_x,p_y,size_x,size_y) &&
        check_limit(e_x,e_y,size_x,size_y)) {
            /**ALlocate memory for map, player's x,y positions and enemy information**/
            player_direction = (char*)malloc(sizeof(char));
            dimensions = (int*)malloc(sizeof(int) * 2);
            enemy_pos = (int*)malloc(sizeof(int) * 2);
            enemy_pos[0] = e_x;
            enemy_pos[1] = e_y;
            dimensions[0] = size_x;
            dimensions[1] = size_y;
            player_x = &p_y;
            player_y = &p_x;
            /**turns command line value of the character to face of the character on the map **/
            *player_direction = translate_dir(p_dir);
            map = generate_map(size_x,size_y);
            /**Place the player into the map at the beginning**/
            map[*player_y][*player_x] = *player_direction;
            e_dir = translate_dir(e_dir);
            /**Place the enemy into the map at the beginning**/
            update_map(map,dimensions,e_x,e_y,e_dir);
            game_func(map,player_x,player_y,player_direction,dimensions,enemy_pos,e_dir);
            free_map(map,size_y);
            free(dimensions);
            free(player_direction);
            free(enemy_pos);
        }
        else {
            printf("Invalid settings provided\n");
        }
    }
    else {
        printf("Usage: ./laserTank <row_size> <col_size> <player_row> <player_col> <player_direction> <enemy_row> <enemy_col> <enemy_direction>\n");
    }
    return 0;
}

/**Game function that starts the game**/
void game_func(char** map,int* player_x,int* player_y,char* direction,int* dimensions,int* enemy_pos,char enemy) {
    int game_won = FALSE;
    int game_loop = TRUE;
    display_map(map,dimensions[1],0);
    while(game_loop) {
        display_commands();
        game_won = process_action(map,dimensions,player_x,player_y,direction,enemy_pos,enemy);
        display_map(map,dimensions[1],1);
        if(game_won) {
            game_loop = FALSE;
        }
    }
}

/** Evaluates player's input to either move or shoot,
    calls shoot animation or update player position on player input**/
int process_action(char** map,int* dimensions,int* x,int* y, char* direction,int* enemy_pos,char enemy) {
    int win_condition = FALSE;
    char command = get_player_input();
    int* e_x;
    int* e_y;
    command = (command >= 97 && command <= 122) ? command - 32 : command;
    newSleep(0.5);
    if( command == WEST || command == EAST || command == NORTH
        || command == SOUTH) {
            e_x = &enemy_pos[0];
            e_y = &enemy_pos[1];
            printf("Enemy position is: %d,%d\n\n",*e_x,*e_y);
            move_player(map,x,y,direction,dimensions,command);
            if(is_player_on_enemy_direction(enemy,enemy_pos[0],enemy_pos[1],*x,*y)) {
                win_condition = shooting_animation(map,dimensions,e_x,e_y,enemy,*direction);
                if(win_condition == TRUE) {
                    display_player_lost();
                }
            }

    }
    else if(command == SHOOT) {
       win_condition = shooting_animation(map,dimensions,x,y,*direction,enemy);
       if(win_condition == TRUE) {
            display_player_won();
       }
    }
    else {
        printf("Invalid command, try again.\n");
    }
    return win_condition;
}

/** After the player moves to another tile on the map, check if the enemy
    is facing the player**/
int is_player_on_enemy_direction(char enemy_direction, int e_x,int e_y, int p_x,int p_y) {
    int is_facing = FALSE;
    if(enemy_direction == '<') {
        if(e_y == p_y && p_x < e_x) {

            is_facing = TRUE;
        }
    }
    else if(enemy_direction == '>') {
        if(e_y == p_y && p_x > e_x) {
            is_facing = TRUE;
        }
    }
    else if(enemy_direction == 'v') {
        if(e_y < p_y && p_x == e_x) {
            is_facing = TRUE;
        }
    }
    else if(enemy_direction == '^') {
        if(e_y > p_y && p_x == e_x) {
            is_facing = TRUE;
        }
    }
    return is_facing;
}

/**Checks if player inputs are valid or not, returns boolean TRUE/FALSE**/
static int check_dir(char dir) {
    int bool = FALSE;
    if(dir == UP || dir == DOWN  || dir == LEFT || dir == RIGHT) {
        bool = TRUE;
    }
    return bool;
}


/**returns characters of player/enemy back to commands**/
static char translate_dir(char dir) {
    char object_direction = '<';
    if(dir == UP) {
        object_direction = '^';
    }
    else if(dir == DOWN) {
        object_direction = 'v';
    }
    else if(dir == RIGHT) {
        object_direction = '>';
    }
    else if(dir == LEFT) {
        object_direction = '<';
    }
    return object_direction;
}
