#ifndef CONTROLLER_H
#define CONTROLLER_H

char get_player_input();
int get_map_size_y(char**);
void move_player(char**,int*,int*,char*,int*,char);
int check_bounds(int,int,int*,char**);
int check_limit(int,int,int,int);
int check_direction(char);
#endif
