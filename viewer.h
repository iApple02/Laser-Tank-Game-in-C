#ifndef VIEWER_H
#define VIEWER_H
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define DEFAULT "\033[0m"
#define PRINTCOLOR(l,c) printf("%s%c%s",c,l,DEFAULT)

int shootingAnimation(char** map, int* dimensions, int* row, int* col, char direction, char opponent);
int getNumFrames(int* dimensions,int laserRow ,int laserCol,int row,int col);
void displayMap(char** map, int col, int mode);
void displayCommands();
void laserRowCol(int* laserRow, int* laserCol, char direction,char* laserDirection);
int hasBullet(char pos);
void printColours(char* line,int mode);
void displayPlayerWon(); 
void displayPlayerLost(); 

#endif
