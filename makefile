#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

# Compilation of all files must be enabled using the command 'Make all'
# Make clean must delete all craft
# Exe files will called: mytee.c --> mytee, mync.c --> mync, myshell.c --> myshell

CC = gcc
AR = ar
FLAGS = -Wall -g

run: main
	./main

all: main

main: main.o
	$(CC) -pthread -o main main.c utils.h mutex.c pipe.c cond.c utils.c fcntl.c $(FLAGS)

.PHONY: clean all

#clean all files
clean:
	rm -f *.o *.so utils main