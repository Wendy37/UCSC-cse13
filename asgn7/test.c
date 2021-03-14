#include "test.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <math.h>
#include "word.h"
#include "io.h"
#include "trie.h"

int main(void) {
    int value = log2(31)+1;
    printf("%d\n", value);
    return 0;
}
