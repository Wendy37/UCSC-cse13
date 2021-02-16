#include "globe.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct globe {
    uint32_t moves;
    uint32_t comp;
};

globe *g_create(void) {
    globe *g = calloc(1, sizeof(globe));
    g->comp = 0;
    g->moves = 0;
    return g;
}

bool swap(uint32_t *A, int64_t a, int64_t b, globe *g) {
    g->moves += 3;
    uint32_t temp = A[a];
    A[a] = A[b];
    A[b] = temp;
    return true;
}

bool comparison(int64_t a, int64_t b, globe *g) {
    g->comp += 1;
    if (a < b) {
        return true;
    }
    return false;
}

uint32_t count(globe *g) {
    return g->comp;
}

uint32_t moves(globe *g) {
    return g->moves;
}

void delete_g(globe *g) {
    free(g);
    g = NULL;
}

void print_array(uint32_t *A,
    uint32_t n) { // print specific number of elements in the array
    uint32_t index = 0;
    uint32_t row = n / 5;
    if (n % 5 != 0) {
        row++;
    }
    while (row) {
        for (uint32_t j = 0; j < 5 && index < n; j++) {
            printf("%13" PRIu32, A[index]);
            index++;
        }
        printf("\n");
        row--;
    }
}
