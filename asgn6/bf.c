#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "bf.h"
#include "bv.h"
#include "speck.h"

struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size){
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf){
        bf->primary[0] = 0x02d232593fbe42ff;
        bf->primary[1] = 0x3775cfbf0794f152;
        bf->secondary[0] = 0xc1706bc17ececc04;
        bf->secondary[1] = 0xe9820aa4d2b8261a;
        bf->tertiary [0] = 0xd37b01df0ae8f8d0;
        bf->tertiary [1] = 0x911d454886ca7cf7;
        bf->filter = bv_create(size);
        printf("bv size: %d\n", bv_length(bf->filter));
        if(!bf->filter){
            free(bf);
            bf = NULL;
            printf("bv not generated\n");
        }
    }
    return bf;
}

void bf_delete(BloomFilter **bf){
    free((*bf)->filter);
    free(*bf);
    *bf = NULL;
}

uint32_t bf_length(BloomFilter *bf){
    return bv_length(bf->filter);
}

void test_prim(BloomFilter *bf){
    printf("%llu\n", bf->primary[1]);
}

void bf_insert(BloomFilter *bf, char *oldspeak){ // err
    printf("inside bf_insert\n");
    printf("%llu\n", bf->primary[1]); // err
    uint32_t index1 = hash(bf->primary, oldspeak) % bf_length(bf);
    printf("index1 = %d\n", index1);
    uint32_t index2 = hash(bf->secondary, oldspeak) % bf_length(bf);
    uint32_t index3 = hash(bf->tertiary, oldspeak) % bf_length(bf);
    
    bv_set_bit(bf->filter, index1);
    printf("hash done\n");
    bv_set_bit(bf->filter, index2);
    bv_set_bit(bf->filter, index3);
}

bool bf_probe(BloomFilter *bf, char *oldspeak){
    uint32_t index1 = hash(bf->primary, oldspeak) % bf_length(bf);
    uint32_t index2 = hash(bf->secondary, oldspeak) % bf_length(bf);
    uint32_t index3 = hash(bf->tertiary, oldspeak) % bf_length(bf);
    if(bv_get_bit(bf->filter, index1) & bv_get_bit(bf->filter, index2) & bv_get_bit(bf->filter, index3)){
        return true;
    }
    return false;
}

void bf_print(BloomFilter *bf){
    for (uint32_t i = 0; i < bf_length(bf); i++) {
        printf("%d ", bv_get_bit(bf->filter, i));
    }
}
