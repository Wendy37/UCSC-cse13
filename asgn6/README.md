# Assignment 6
This program implements Bloom Filter and Hash Table to store and search words from intext message that are forbidden, known as badspeak, and oldspeak which need to be translated into the corresponding newspeak. Then messaged will show notifying users what words are not allowed to use and what need to be translated. All badspeak and oldspeak-newspeak pairs are inserted into bloom filter and hash table beforehand.

## Build
    $ clang -Wall -Wextra -Werror -Wpedantic -c banhammer.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c hash.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c bf.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c bv.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c ll.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c node.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c parser.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c speck.c
    $ clang -o banhammer banhammer.o hash.o bf.o bv.o ll.o node.o parser.o speck.o -lm
    
## Cleaning
    $ rm -f banhammer *.o
