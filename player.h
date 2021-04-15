#ifndef PLAYER_H
#define PLAYER_H
int get_direction();
void delta_player(int*,int*,char);
void update_position(char**,int*,int*,int,int,int*);
char get_character(char);
char get_character_direction(char);
void change_direction(char**,int*,int*,char*,int*,char);
void set_character_direction(char*,char);
#endif
