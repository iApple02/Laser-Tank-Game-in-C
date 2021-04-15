#ifndef VIEWER_H
#define VIEWER_H
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define DEFAULT "\033[0m"
#define PRINT_COLOR(l,c) printf("%s%c%s",c,l,DEFAULT)

int shooting_animation(char**,int*,int*,int*,char,char);
int has_bullet(char);
int get_num_frames(int*,int,int,int,int);
void display_map(char**,int,int);
void display_player_won();
void display_player_lost();
void display_commands();
void delta_x_y(int*,int*,char,char*);
void print_colors(char*,int);

#endif
