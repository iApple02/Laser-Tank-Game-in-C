CC = gcc
CFLAGS = -Wall -pedantic -ansi -g
OBJ = main.o map.o movement.o newSleep.o player.o viewer.o
EXEC = laserTank
$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)
main.o : main.c map.c movement.c newSleep.c player.c viewer.c
	$(CC) -c main.c $(CFLAGS)
clean:
	rm -f $(EXEC) $(OBJ)
