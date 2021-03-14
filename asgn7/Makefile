CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

encode: encode.o io.o trie.o
	$(CC) -o encode encode.o io.o trie.o -lm
	
encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c
	
io.o: io.c
	$(CC) $(CFLAGS) -c io.c
	
trie.o: trie.c
	$(CC) $(CFLAGS) -c trie.c
	
decode: decode.o io.o word.o
	$(CC) -o decode decode.o io.o word.o -lm
	
decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c
	
word.o: word.c
	$(CC) $(CFLAGS) -c word.c
	
clean:
	rm -f encode decode *.o

