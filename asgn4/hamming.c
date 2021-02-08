#include <stdint.h>
#include <stdio.h>
#include "hamming.h"
#include "bm.h"

static BitMatrix *generator; //G
static BitMatrix *parity;    //H
static int lookup[16] = {0, 4, 5, -1, 6, -1, -1, 3, 7, -1, -1, 2, -1, 1, 0, -1};

void int_to_mat(uint8_t integer, BitMatrix *m){ // convert integer to a bit matrix
    uint8_t mask;
    uint8_t bit;
    for(uint8_t i = 0; i < bm_cols(m); i++){
        mask = 1 << i;
        bit = (mask & integer) >> i;
        if(bit == 1){
            bm_set_bit(m, 0, i);
        }
    }
}

uint8_t mat_to_int(BitMatrix *m){    // convert a (1*8) matrix to a byte
    uint8_t integer = 0;
    uint8_t mask;
    uint8_t bit;
    for(uint8_t i = 0; i < 8; i++){
        mask = bm_get_bit(m, 0, i);
        bit = mask << i;
        integer = integer | bit;
    }
    return integer;
}

void mat_mult(BitMatrix *a, BitMatrix *b, BitMatrix *c){     // matrices multiplication a = b * c
    uint8_t bit;
    for(uint32_t i = 0; i < bm_rows(b); i++){
        for(uint32_t j = 0; j < bm_cols(c); j++){
            bit = 0;
            for(uint32_t k = 0; k < bm_rows(c); k++){
                bit += bm_get_bit(b, i, k) * bm_get_bit(c, k, j);
            }
            bit = bit % 2;
            if(bit == 1){
                bm_set_bit(a, i, j);
            }
        }
    }
}

ham_rc ham_init(void){
    generator = bm_create(4, 8);
    bm_set_bit(generator, 0, 0);
    bm_set_bit(generator, 1, 1);
    bm_set_bit(generator, 2, 2);
    bm_set_bit(generator, 3, 3);
    bm_set_bit(generator, 0, 5);
    bm_set_bit(generator, 0, 6);
    bm_set_bit(generator, 0, 7);
    bm_set_bit(generator, 1, 4);
    bm_set_bit(generator, 1, 6);
    bm_set_bit(generator, 1, 7);
    bm_set_bit(generator, 2, 4);
    bm_set_bit(generator, 2, 5);
    bm_set_bit(generator, 2, 7);
    bm_set_bit(generator, 3, 4);
    bm_set_bit(generator, 3, 5);
    bm_set_bit(generator, 3, 6);
    parity = bm_create(8, 4);
    bm_set_bit(parity, 0, 1);
    bm_set_bit(parity, 0, 2);
    bm_set_bit(parity, 0, 3);
    bm_set_bit(parity, 1, 0);
    bm_set_bit(parity, 1, 2);
    bm_set_bit(parity, 1, 3);
    bm_set_bit(parity, 2, 0);
    bm_set_bit(parity, 2, 1);
    bm_set_bit(parity, 2, 3);
    bm_set_bit(parity, 3, 0);
    bm_set_bit(parity, 3, 1);
    bm_set_bit(parity, 3, 2);
    bm_set_bit(parity, 4, 0);
    bm_set_bit(parity, 5, 1);
    bm_set_bit(parity, 6, 2);
    bm_set_bit(parity, 7, 3);
    if(generator == NULL | parity == NULL){
        return HAM_ERR;
    }
    else{
        return HAM_OK;
    }
}

void ham_destroy(void){
    bm_delete(&generator);
    bm_delete(&parity);
}

ham_rc ham_encode(uint8_t data, uint8_t *code){
    BitMatrix *data_v = bm_create(1, 4); // convert data to vector data_v
    BitMatrix *code_v = bm_create(1, 8);

    int_to_mat(data, data_v);
    
    mat_mult(code_v, data_v, generator); // code_v = data_v * generator

    *code = mat_to_int(code_v);     // convert code_v to code (uint8_t)
    
    if(code == NULL | data_v == NULL | code_v == NULL){
        return HAM_ERR;
    }
    else{
        return HAM_OK;
    }
}



ham_rc ham_decode(uint8_t code, uint8_t *data){
    BitMatrix *code_v = bm_create(1, 8); // convert code to vector code_v
    BitMatrix *error_v = bm_create(1, 4);

    int_to_mat(code, code_v);
    mat_mult(error_v, code_v, parity);     // error = code_v * parity
    
    uint8_t error = mat_to_int(error_v);   // find error that can be corrected
    if(code_v == NULL | data == NULL | error_v==NULL){
        return HAM_ERR;
    }
    int index = -1;
    if(error < 16 && error > 0){
        index = lookup[error];
    }else if (error == 0){
        return HAM_OK;
    }
    
    if (index != -1){                     // correct the error in code_v
        if(bm_get_bit(code_v, 0, index) == 0){
            bm_set_bit(code_v, 0, index);
        }else{
            bm_clr_bit(code_v, 0, index);
        }
        *data = mat_to_int(code_v) & 0xF;
        //printf("data = %d\n", *data);
        return HAM_ERR_OK;
    } else{
        return HAM_ERR;
    }
}
