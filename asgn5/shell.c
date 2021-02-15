#include <stdio.h>
#include <stdint.h>
#include "shell.h"
#include "gaps.h"
#include "globe.h"

void shell_sort(uint32_t *A, uint32_t n){
    uint32_t index = 0;      //index of gaps[]
    while(gaps[index] >= n){
        index++;
    }
    uint32_t comp = 0;
    for (uint32_t k = index; k < 102; k++){
        uint32_t gap = gaps[k];
        for(uint32_t i = gap; i < n; i++){
            uint32_t j = i;
            uint32_t temp = A[i];
            while(j >= gap && comparison(temp, A[j-gap], &comp)){
                swap(A, j, j-gap);
                j -= gap;
            }
            A[j] = temp;
        }
    }
}

