CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: life

life: life.o universe.o
	$(CC) -o life life.o -lncurses universe.o -lm 

life.o: life.c
	$(CC) $(CFLAGS) -c life.c

universe.o: universe.c
	$(CC) $(CFLAGS) -c universe.c

clean: 
	rm -f life *.o

