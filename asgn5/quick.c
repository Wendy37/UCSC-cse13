#include <stdint.h>
#include <stdio.h>
#include "quick.h"
#include "globe.h"
#include "stack.h"

uint64_t partition(uint32_t *A, int64_t lo, int64_t hi, globe *g_q){
    uint32_t pivot = A[lo + ((hi - lo) / 2)];
    int64_t i = lo-1;
    int64_t j = hi+1;
    while(i < j){
        i+=1;
        while (count(g_q) && comparison(A[i], pivot)){
            i += 1;
        }
        j -= 1;
        while (count(g_q) && comparison(pivot, A[j])){
            j -= 1;

        }
        if(count(g_q) && comparison(i, j)){
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
    globe *g_q = g_create(1, 0);
    Stack *stack = stack_create();
    stack_push(stack, left);
    stack_push(stack, right);
    while (!stack_empty(stack)){
        stack_pop(stack, &hi);//////////////
        stack_pop(stack, &lo);
        int64_t p = partition(A, lo, hi, g_q);
        if( count(g_q) && comparison(p+1, hi)){
            stack_push(stack, (p + 1));
            stack_push(stack, hi);
        }
        if(count(g_q) && comparison(lo, p)){
            stack_push(stack, lo);
            stack_push(stack, p);
        }
    }
    printf("Quick Sort\n");
    printf("%d elements, %d compares\n", n, count(g_q)-1);}
