#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controller.h"
#include "map.h"

void update_map(char** map,int* dimensions,int new_x,int new_y,char direction) {
    if(check_bounds(new_x,new_y,dimensions,map)) {
        map[new_y][new_x] = direction;
    }
}

char** generate_map(int size_x,int size_y) {
    int i;
    char** map = (char**)malloc(sizeof(char*) * size_y);
    for(i=0;i<size_y;i++) {
        char* line = (char*)malloc(sizeof(char)* size_x);
        memset(line,' ',size_x);
        map[i] = line;
    }
    return map;
}

void free_map(char** map,int y) {
    int i;
    for(i=0;i<y;i++){
        free(map[i]);
    }
    free(map);
}
