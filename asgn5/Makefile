CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: sorting

sorting: sorting.o bubble.o shell.o quick.o heap.o globe.o set.o stack.o
	$(CC) -o sorting sorting.o bubble.o shell.o quick.o heap.o globe.o set.o stack.o -lm

bubble.o: bubble.c
	$(CC) $(CFLAGS) -c bubble.c
	
sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c
	
globe.o: globe.c
	$(CC) $(CFLAGS) -c globe.c

set.o: set.c
	$(CC) $(CFLAGS) -c set.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c
	
stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

heap.o: heap.c
	$(CC) $(CFLAGS) -c heap.c
	
clean:
	rm -f sorting *.o

format:
	clang-format -i --style=file *.[ch]
