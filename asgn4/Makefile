CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: generator decoder err

generator: generator.o hamming.o bm.o
	$(CC) -o generator generator.o bm.o hamming.o -lm

generator.o: generator.c
	$(CC) $(CFLAGS) -c generator.c

hamming.o: hamming.c
	$(CC) $(CFLAGS) -c hamming.c

bm.o: bm.c
	$(CC) $(CFLAGS) -c bm.c
	
decoder: decoder.o hamming.o bm.o
	$(CC) -o decoder decoder.o bm.o hamming.o -lm

decoder.o: decoder.c
	$(CC) $(CFLAGS) -c decoder.c
	
err: error.o
	$(CC) -o err error.o
error.o: error.c
	$(CC) $(CFLAGS) -c error.c
	
clean:
	rm -f generator err decoder *.o

