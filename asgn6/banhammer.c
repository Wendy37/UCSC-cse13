#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "hash.h"
#include "banhammer.h"
#include "parser.h"
#include "bf.h"
#include "bv.h"

// test!!!!!
int main(){
    FILE *infile = fopen("test.txt", "r");
    BloomFilter *bf = bf_create(40);
    test_prim(bf);
    char oldspeak;
    while (!feof(infile)){
        test_prim(bf);
        fscanf(infile, "%s\n", &oldspeak); // ok
        test_prim(bf);
        bf_insert(bf, &oldspeak); // err
    }
    printf("Bloom Filter test:\n");
    bf_print(bf);
    bf_delete(&bf);
    fclose(infile);
    return 0;
    /*BloomFilter *bf = bf_create(10);
    printf("1");
    HashTable *ht = ht_create(10, false);
    printf("2");
    FILE *infile = fopen("test.txt", "r");
    printf("3");
    //FILE *outfile = stdout;
    char oldspeak;
    while (!feof(infile)){
        printf("4");
        fscanf(infile, "%s\n", &oldspeak);
        bf_insert(bf, &oldspeak);
        ht_insert(ht, &oldspeak, NULL);
    }
    
    printf("Bloom Filter test:\n");
    bf_print(bf);
    printf("Hash Table test:\n");
    ht_print(ht);
    return 0;*/
}
