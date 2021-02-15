#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"
#include "globe.h"

uint32_t max_child(uint32_t *A, uint32_t first, uint32_t last, globe *H){
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    if(right <= last && comparison(A[left - 1], A[right - 1], H)){
        return right;
    }
    return left;
}

void fix_heap(uint32_t *A, uint32_t first, uint32_t last, globe *H){
    bool found = false;
    uint32_t parent = first;
    uint32_t great = max_child(A, parent, last, H);
    
    while( (parent <= last / 2) && !(found)){
        if (comparison(A[parent - 1], A[great - 1], H)){
            swap(A, parent-1, great-1, H);
            parent = great;
            great = max_child(A, parent, last, H);
        } else{
            found = true;
        }
    }
}

void build_heap(uint32_t *A, uint32_t first, uint32_t last, globe *H){
    for (uint32_t parent = last / 2; parent > first - 1; parent += -1){
        fix_heap(A, parent, last, H);
    }
}

void heap_sort(uint32_t *A, uint32_t n){
    globe *H = g_create();
    uint32_t first = 1;
    uint32_t last = n;
    build_heap(A, first, last, H);
    for(uint32_t leaf = last; leaf > first; leaf -= 1){
        swap(A, first-1, leaf-1, H);
        fix_heap(A, first, leaf-1, H);
    }
    printf("Heap Sort\n");
    printf("%d elements, %d moves, %d compares\n", n, moves(H), count(H));
    delete_g(&H);
}
