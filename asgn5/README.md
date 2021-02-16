# Assignment 5
This program implements 4 sorting algorithms including bubble sort, shell sort, quick sort, and heap sort. When executing each sort, the operations will be counted.

## Build
    $ clang -Wall -Wextra -Werror -Wpedantic -c sorting.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c bubble.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c shell.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c quick.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c heap.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c globe.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c set.c
    $ clang -Wall -Wextra -Werror -Wpedantic -c stack.c
    $ clang -o sorting sorting.o bubble.o shell.o quick.o heap.o globe.o set.o stack.o -lm
    
## Cleaning
    $ rm -f sorting *.o
