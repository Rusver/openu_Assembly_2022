
OBJ = files main preprocessor
CC=gcc 
CFLAGS =-Wall -pedantic -ansi

all: program1

program1:
	$(CC) $(CFLAGS) -g -o a1 preprocessor.c parcer.c files.c main.c

