CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: banhammer

banhammer: banhammer.o hash.o bf.o bv.o ll.o node.o parser.o speck.o
	$(CC) -o banhammer banhammer.o hash.o bf.o bv.o ll.o node.o parser.o speck.o -lm

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

hash.o: hash.c
	$(CC) $(CFLAGS) -c hash.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

ll.o: ll.c
	$(CC) $(CFLAGS) -c ll.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

clean:
	rm -f banhammer *.o
