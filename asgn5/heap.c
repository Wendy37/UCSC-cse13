#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"
#include "globe.h"

uint32_t max_child(uint32_t *A, uint32_t first, uint32_t last){
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    if(right <= last && comparison(A[left - 1], A[right - 1])){
        return right;
    }
    return left;
}

void fix_heap(uint32_t *A, uint32_t first, uint32_t last){
    bool found = false;
    uint32_t parent = first;
    uint32_t great = max_child(A, parent, last);
    
    while( (parent <= last / 2) && !(found)){
        if (comparison(A[parent - 1], A[great - 1])){
            swap(A, parent-1, great-1);
            parent = great;
            great = max_child(A, parent, last);
        } else{
            found = true;
        }
    }
}

void build_heap(uint32_t *A, uint32_t first, uint32_t last){
    for (uint32_t parent = last / 2; parent > first - 1; parent += -1){
        fix_heap(A, parent, last);
    }
}

void heap_sort(uint32_t *A, uint32_t n){
    uint32_t first = 1;
    uint32_t last = n;
    uint32_t comp = 0;
    build_heap(A, first, last);
    for(uint32_t leaf = last; leaf > first; leaf -= 1){
        swap(A, first-1, leaf-1);
        fix_heap(A, first, leaf-1);
    }
    printf("comp = %d\n", comp);
}
