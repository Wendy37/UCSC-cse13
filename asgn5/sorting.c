#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "bubble.h"
#include "globe.h"
#include "shell.h"
#include "quick.h"
#include "heap.h"
#include "set.h"

#define OPTIONS "absqhr:n:p:"

typedef enum Sorts{     // index
    bubble = 0,
    shell = 1,
    quick = 2,
    heap = 3
} Sorts;

void fill_array(uint32_t *A, uint32_t size, uint32_t seed){
    srand(seed);
    for (uint32_t i = 0; i < size; i++){
        A[i] = rand() & ~(1 << 30);
    }
}

int main(int argc, char **argv){
    int opt = 0;
    Set s = set_empty();
    uint32_t seed = 7092016;
    char temp[100];
    uint32_t size = 100;
    uint32_t print_elem = 100;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt){
            case 'a':
                s = set_insert(s, bubble);
                s = set_insert(s, shell);
                s = set_insert(s, quick);
                s = set_insert(s, heap);
                break;
            case 'b':
                s = set_insert(s, bubble);
                break;
            case 's':
                s = set_insert(s, shell);
                break;
            case 'q':
                s = set_insert(s, quick);
                break;
            case 'h':
                s = set_insert(s, heap);
                break;
            case 'r':
                strcpy(temp, optarg);
                sscanf(temp, "%d", &seed);
                break;
            case 'n':
                strcpy(temp, optarg);
                sscanf(temp, "%d", &size);
                break;
            case 'p':
                strcpy(temp, optarg);
                sscanf(temp, "%d", &print_elem);
                break;
            default: fprintf(stderr, "Usage: %s -[absqhr:n:p:]\n", argv[0]);
                break;
        }
    }
    uint32_t *A = malloc(size * sizeof(uint32_t));
    if (print_elem > size){ print_elem = size; }
    
    if(set_member(s, bubble)){
        fill_array(A, size, seed);
        bubble_sort(A, size);
        print_array(A, print_elem);
    }
    if(set_member(s, shell)){
        fill_array(A, size, seed);
        shell_sort(A, size);
        print_array(A, print_elem);
    }
    if(set_member(s, quick)){
        fill_array(A, size, seed);
        quick_sort(A, size);
        print_array(A, print_elem);
    }
    if(set_member(s, heap)){
        fill_array(A, size, seed);
        heap_sort(A, size);
        print_array(A, print_elem);
    }
    
    return 0;
}
