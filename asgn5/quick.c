#include <stdint.h>
#include <stdio.h>
#include "quick.h"
#include "globe.h"
#include "stack.h"

uint64_t partition(uint32_t *A, int64_t lo, int64_t hi){
    uint32_t pivot = A[lo + ((hi - lo) / 2)];
    int64_t i = lo-1;
    int64_t j = hi+1;
    while(i < j){
        i+=1;
        while (count() && comparison(A[i], pivot)){
            i += 1;
        }
        j -= 1;
        while (count() && comparison(pivot, A[j])){
            j -= 1;

        }
        if(count() && comparison(i, j)){
            swap(A, i, j);
        }
    }
    return j;
}


void quick_sort(uint32_t *A, uint32_t n){
    uint32_t left = 0;
    uint32_t right = n-1;
    int64_t hi = 0;
    int64_t lo = 0;
    uint32_t reset;
    
    Stack *stack = stack_create();
    stack_push(stack, left);
    stack_push(stack, right);
    while (!stack_empty(stack)){
        stack_pop(stack, &hi);
        stack_pop(stack, &lo);
        int64_t p = partition(A, lo, hi);
        if( comparison(p+1, hi)){
            stack_push(stack, (p + 1));
            stack_push(stack, hi);
        }
        if( comparison(lo, p)){
            stack_push(stack, lo);
            stack_push(stack, p);
        }
    }
    printf("Quick Sort\n");
    printf("%d elements, %d compares\n", n, count()-2);
    reset = count()-count();
   }
