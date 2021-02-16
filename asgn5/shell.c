#include "shell.h"

#include "gaps.h"
#include "globe.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void shell_sort(uint32_t *A, uint32_t n) {
    globe *S = g_create();
    uint32_t index = 0; // index of gaps[]
    while (gaps[index] >= n) {
        index++;
    }
    for (uint32_t k = index; k < 102; k++) {
        uint32_t gap = gaps[k];
        for (uint32_t i = gap; i < n; i++) {
            uint32_t j = i;
            uint32_t temp = A[i];
            while (j >= gap && comparison(temp, A[j - gap], S)) {
                swap(A, j, j - gap, S);
                j -= gap;
            }
            A[j] = temp;
        }
    }
    printf("Shell Sort\n");
    printf("%d elements, %d moves, %d compares\n", n, moves(S), count(S));
    delete_g(S);
}
