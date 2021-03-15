# Assignment 7
This program compresses and decompresses files with lossless compression – Lempel-Ziv Compression. The compression algorithms encode data with repeated patterns using code-symbol pair using trie, and decompression decode with a Word ADT. And the helper file io.c for reading and writing bytes to infile and outfile.

## Build
    $ clang -Wall -Wextra -Werror -Wpedantic -c encode.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c io.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c trie.c
    $ clang -o encode encode.o io.o trie.o -lm
    $ clang -Wall -Wextra -Werror -Wpedantic -c decode.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c word.c
    $ clang -o decode decode.o io.o word.o -lm
## Cleaning
    $ rm -f encode decode *.o

## Options of encode
    -v Print statistics to stderr.
    -i <input>:Specify input to compress (stdin by default)
    -o <output>:Specify output of compressed input (stdout by default)
    
## Options of decode
    -v Print statistics to stderr.
    -i <input>:Specify input to decompress (stdin by default)
    -o <output>:Specify output of decompressed input (stdout by default)
