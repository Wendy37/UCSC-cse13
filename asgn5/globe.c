#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include "globe.h"

uint32_t A[11] = {15768739, 246783, 37833, 4234, 597036, 63274839, 726738, 8234, 0, 1, 7};

void swap(uint32_t *A, int64_t a, int64_t b){
    uint32_t temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}

uint32_t count(void){
    static uint32_t c = 1;
    c++;
    return c;
}

bool comparison(int64_t a, int64_t b){
    if(a < b){
        return true;
    }
    return false;
}

void print_array(uint32_t *A, uint32_t n){ // print specific number of elements in the array
    uint32_t index = 0;
    uint32_t row = n / 5;
    if (n % 5 != 0){
        row++;
    }
    while(row){
        for(uint32_t j = 0; j < 5 && index < n; j++){
            printf("%13" PRIu32, A[index]);
            index++;
        }
        printf("\n");
        row--;
    }
}
