#include "bubble.h"

#include "globe.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void bubble_sort(uint32_t *A,
    uint32_t n) { // A is array, n is length/elements of the array
    uint32_t size = n;
    globe *B = g_create();

    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (uint32_t i = 1; i < n; i++) {
            if (comparison(A[i], A[i - 1], B)) {
                swap(A, i, i - 1, B);
                swapped = true;
            }
        }
        n -= 1;
    }
    printf("Bubble Sort\n");
    printf("%d elements, %d moves, %d compares\n", size, moves(B), count(B));
    delete_g(B);
}
