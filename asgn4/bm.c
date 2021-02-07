#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "bm.h"

struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    uint8_t **mat;
};

uint32_t byte(uint32_t bits){
    return bits % 8 == 0 ? bits/8 : (bits/8)+1;
}

BitMatrix *bm_create(uint32_t rows, uint32_t cols){
    BitMatrix *m = (BitMatrix *)calloc(1, sizeof( BitMatrix ));
    m->rows = rows;
    m->cols = cols;
    m->mat = (uint8_t **)calloc(rows, sizeof(uint32_t *));
    for (uint32_t i = 0;i < rows; i++){
        m->mat[i] = (uint8_t *)calloc(byte(cols), sizeof(uint8_t));
    }
    for (uint32_t i = 0; i < rows; i++){
        for (uint8_t j = 0; j < byte(cols); j++){
            m->mat[i][j] = 0;
        }
    }
    return m;
}

void bm_delete(BitMatrix **m){
    for (uint32_t i = 0; i < (*m)->rows; i++) {
        free((*m)->mat[i]);
    }
    free((*m)->mat);
    free(*m);
    *m = NULL;
    return ;
}

uint32_t bm_rows(BitMatrix *m){
    return m->rows;
}

uint32_t bm_cols(BitMatrix *m){
    return m->cols;
}

void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c){
    uint8_t byte = m->mat[r][c / 8];
    c = c % 8;
    uint8_t mask = 1 << c;
    m->mat[r][c / 8] = byte | mask;
    return ;
}

void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c){
    uint8_t byte = m->mat[r][c / 8];
    c = c % 8;
    uint8_t mask = ~(1 << c);
    m->mat[r][c / 8] = byte & mask;
    return ;
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c){
    uint8_t byte = m->mat[r][c / 8];
    c = c % 8;
    uint8_t mask = 1 << c;
    uint8_t result = byte & mask;
    result = result >> c;
    return result;
}

void bm_print(BitMatrix *m){
    for (uint32_t i = 0; i < bm_rows(m); i++){
        for(uint32_t j = 0; j < bm_cols(m); j++){
            printf("%d ", bm_get_bit(m, i, j));
        }
        printf("\n");
    }
    return;
}
