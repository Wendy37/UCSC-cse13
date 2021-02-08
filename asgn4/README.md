# Assignment 4
This lab contains two programs, generator and decoder, which are able to generate hamming codes from original messages, and decode hamming code with corrections on some specific errors then return the corrected original message respectively. The other program err can inject errors into the hamming codes for testing the programs. 

## Build
    $ clang -Wall -Wextra -Werror -Wpedantic -c generator.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c hamming.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c bm.c
    $ clang -o generator generator.o bm.o hamming.o -lm
    $ clang -Wall -Wextra -Werror -Wpedantic -c decoder.c
    $ clang -o decoder decoder.o bm.o hamming.o -lm
    $ clang -Wall -Wextra -Werror -Wpedantic -c error.c
    $ clang -o err error.o
    
## Cleaning
    $ rm -f gen err dec *.o
