#include "bv.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    BitVector *b = (BitVector *) calloc(1, sizeof(BitVector));
    b->length = length;
    b->vector = (uint8_t *) calloc(length / 8 + 1, sizeof(uint8_t));
    return b;
}

void bv_delete(BitVector **bv) {
    free((*bv)->vector);
    free(*bv);
    *bv = NULL;
}

uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

void bv_set_bit(BitVector *bv, uint32_t i) {
    uint8_t byte = bv->vector[i / 8];
    uint8_t mask = 1 << i % 8;
    bv->vector[i / 8] = byte | mask;
}

void bv_clr_bit(BitVector *bv, uint32_t i) {
    uint8_t byte = bv->vector[i / 8];
    uint8_t mask = ~(1 << i % 8);
    bv->vector[i / 8] = byte & mask;
}

uint8_t bv_get_bit(BitVector *bv, uint32_t i) {
    uint8_t byte = bv->vector[i / 8];
    uint8_t mask = 1 << i % 8;
    uint8_t result = byte & mask;
    result = result >> i % 8;
    return result;
}

void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < bv_length(bv); i++) {
        printf("%d ", bv_get_bit(bv, i));
    }
    printf("\n");
}
