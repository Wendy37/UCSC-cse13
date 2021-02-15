#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "quick.h"
#include "globe.h"
#include "stack.h"

uint64_t partition(uint32_t *A, int64_t lo, int64_t hi, globe *Q){
    uint32_t pivot = A[lo + ((hi - lo) / 2)];
    int64_t i = lo-1;
    int64_t j = hi+1;
    while(i < j){
        i+=1;
        while (comparison(A[i], pivot, Q)){
            i += 1;
        }
        j -= 1;
        while (comparison(pivot, A[j], Q)){
            j -= 1;
        }
        if(i < j){
            swap(A, i, j, Q);
        }
    }
    return j;
}


void quick_sort(uint32_t *A, uint32_t n){
    globe *Q = g_create();
    uint32_t left = 0;
    uint32_t right = n-1;
    int64_t hi = 0;
    int64_t lo = 0;
    Stack *stack = stack_create();
    stack_push(stack, left);
    stack_push(stack, right);
    while (!stack_empty(stack)){
        stack_pop(stack, &hi);
        stack_pop(stack, &lo);
        int64_t p = partition(A, lo, hi, Q);
        if(comparison(p+1, hi, Q)){
            stack_push(stack, (p + 1));
            stack_push(stack, hi);
        }
        if(comparison(lo, p, Q)){
            stack_push(stack, lo);
            stack_push(stack, p);
        }
    }
    printf("Quick Sort\n");
    printf("%d elements, %d moves, %d compares\n", n, moves(Q), count(Q));
    delete_g(&Q);
}


