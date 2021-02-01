# Assignment 3
This program displays generations of a 2-D grid containing live and dead cells, represents a universe (flat or toroidal). 

## Build
    $ clang -Wall -Wextra -Werror -Wpedantic -c life.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c universe.c
    $ clang -o life life.o -lncurses universe.o -lm 
    
## Cleaning
    $ rm -f life life.o universe.o
