#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include "hash.h"
#include "banhammer.h"
#include "parser.h"
#include "bf.h"
#include "hash.h"
#include "node.h"
#include "ll.h"

// test!!!!!
int main(){
    //BloomFilter *bf = bf_create(10);
    HashTable *ht = ht_create(10, false);
    FILE *infile = fopen("test.txt", "r");
    /*char badspeak1[50];
    char badspeak2[50];
    fscanf(infile, "%s\n", badspeak1);
    ht_insert(ht, badspeak1, NULL);
    fscanf(infile, "%s\n", badspeak2);
    ht_insert(ht, badspeak2, NULL);
    
    ht_print(ht);*/
    char badspeak[1024];
    while( !feof(infile)){
        fscanf(infile, "%s\n", badspeak);
        printf("badspeak: %s\n", badspeak);
        ht_insert(ht, badspeak, NULL);
    }
    ht_print(ht);
    //HashTable *ht = ht_create(10, false);
    /*ht_insert(ht, "wendi", "good");
    ht_insert(ht, "ghjk", "alsk");
    ht_insert(ht, "ghjk", NULL);
    ht_print(ht);*/
    
    return 0;
}
