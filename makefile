
OBJ = files main preprocessor
CC=gcc 
CFLAGS =-Wall -pedantic -ansi

all: program1

program1:
	$(CC) $(CFLAGS) -g -o a1 base_helper.c preprocessor.c parser.c files.c main.c

