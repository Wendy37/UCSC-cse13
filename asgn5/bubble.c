#include <stdio.h>
#include <stdbool.h>
#include "bubble.h"
#include "globe.h"

void bubble_sort(uint32_t *A, uint32_t n){  // A is array, n is length/elements of the array
    uint32_t size = n;
    globe *g_b = g_create(1, 0);
    bool swapped = true;
    while(swapped){
        swapped = false;
        for(uint32_t i = 1; i < n; i++){
            if(count(g_b) && comparison(A[i], A[i-1])){
                swap(A, i, i-1);
                moves(g_b);
                moves(g_b);
                moves(g_b);
                swapped = true;
            }
        }
        n -= 1;
    }
    delete_g(g_b);
    printf("Bubble Sort\n");
    printf("%d elements, %d moves, %d compares\n", size, moves(g_b)-1, count(g_b)-1);
}
