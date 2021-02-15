#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include "globe.h"

struct globe {
    uint32_t comp;
    uint32_t moves;
};

globe *g_create(uint32_t comp, uint32_t moves){
    globe *g = (globe *)calloc(1, sizeof(globe));
    g->comp = comp;
    g->moves = moves;
    return g;
}

void swap(uint32_t *A, int64_t a, int64_t b){
    uint32_t temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}

uint32_t count(globe *g){
    g->comp++;
    return g->comp;
}

uint32_t moves(globe *g){
    g->moves++;
    return g->moves;
}

bool comparison(int64_t a, int64_t b){
    if(a < b){
        return true;
    }
    return false;
}

void print_array(uint32_t *A, uint32_t n){ // print specific number of elements in the array
    uint32_t index = 0;
    uint32_t row = n / 5;
    if (n % 5 != 0){
        row++;
    }
    while(row){
        for(uint32_t j = 0; j < 5 && index < n; j++){
            printf("%13" PRIu32, A[index]);
            index++;
        }
        printf("\n");
        row--;
    }
}
