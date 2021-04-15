CC = gcc
CFLAGS = -Wall -pedantic -ansi -g -Werror
OBJ = main.o controller.o map.o player.o viewer.o newSleep.o
EXEC = laserTank

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : map.c
	$(CC) -c main.c $(CFLAGS)

controller.o : controller.c

map.o : map.c
	$(CC) -c map.c $(CFLAGS)

player.o : player.c
	$(CC) -c player.c $(CFLAGS)

newSleep.o : newSleep.c
	$(CC) -c newSleep.c $(CFLAGS)

viewer.o : viewer.c
	$(CC) -c viewer.c $(CFLAGS)


clean:
	rm -f $(OBJ) $(EXEC)
