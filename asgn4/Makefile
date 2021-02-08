CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: gen dec err 

format: clang-format -i -style=file bm.c decoder.c generator.c error.c hamming.c

gen: gen.o hamming.o bm.o
	$(CC) -o gen gen.o bm.o hamming.o -lm

gen.o: generator.c
	$(CC) $(CFLAGS) -c generator.c

hamming.o: hamming.c
	$(CC) $(CFLAGS) -c hamming.c

bm.o: bm.c
	$(CC) $(CFLAGS) -c bm.c
	
dec: dec.o hamming.o bm.o
	$(CC) -o dec dec.o bm.o hamming.o -lm

dec.o: decoder.c
	$(CC) $(CFLAGS) -c decoder.c
	
err: error.o
	$(CC) -o err error.o
error.o: error.c
	$(CC) $(CFLAGS) -c error.c
	
clean:
	rm -f gen err dec *.o
