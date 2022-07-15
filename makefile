
OBJ = files main preprocessor
CC=gcc 
CFLAGS =-Wall -pedantic -ansi

all: program1 program2

program1:
	$(CC) $(CFLAGS) -o a1 files.c main.c

