#include <stdio.h>
#include <stdbool.h>
#include "bubble.h"
#include "globe.h"

void bubble_sort(uint32_t *A, uint32_t n){  // A is array, n is length/elements of the array
    uint32_t size = n;
    bool swapped = true;
    while(swapped){
        swapped = false;
        for(uint32_t i = 1; i < n; i++){
            if(count() && comparison(A[i], A[i-1])){
                swap(A, i, i-1);
                swapped = true;
            }
        }
        n -= 1;
    }
    printf("Bubble Sort\n");
    printf("%d elements, %d compares\n", size, count()-2);
}
