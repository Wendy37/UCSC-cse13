# Assignment 2
This program has its own functions including Sin(), Cos(), Tan(), Exp(), and Log(), running within certain ranges. The user could enter command line in a format of "./mathlib-test -..".  ".." can be a letter from "asctel" which allow this program to print out result from  all functions, sin, cos, tan, exp, and log in a certain format correspondingly.

## Build
	$ clang -Wall -Werror -Wextra -Wpedantic -c mathlib-test.c
    $ clang -Wall -Werror -Wextra -Wpedantic -c mathlib.c
    $ clang -o mathlib-test mathlib-test.o mathlib.o -lm
    
## Cleaning
    $ rm -f mathlib-test mathlib.o mathlib-test.o
