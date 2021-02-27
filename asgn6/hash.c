#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "ll.h"
#include "speck.h"
#include "node.h"

struct HashTable {
    uint64_t salt [2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};

HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    if (ht) {
        ht->salt[0] = 0x85ae998311115ae3; // Il nome della rosa
        ht->salt[1] = 0xb6fac2ae33a40089;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

void ht_delete(HashTable **ht){
    for(uint32_t i = 0; i < (*ht)->size; i++){
        for(uint32_t j = 0; j < ll_length((*ht)->lists[i]); j++){
            ll_delete(&((*ht)->lists[i]));
        }
    }
    free((*ht)->lists);
    free(*ht);
    *ht = NULL;
}

uint32_t ht_size(HashTable *ht){
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak){
    uint32_t index = hash(ht->salt, oldspeak) % ht_size(ht);
    char *oldcopy = strdup(oldspeak);
    Node *n = ll_lookup(ht->lists[index], oldcopy);
    return n;
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak){
    uint32_t index = hash(ht->salt, oldspeak) % ht_size(ht);
    if( !ht->lists[index]){
        ht->lists[index] = ll_create(ht->mtf);
    }
    ll_insert(ht->lists[index], oldspeak, newspeak);
}

void ht_print(HashTable *ht){
    for(uint32_t i = 0; i < ht->size; i++){
        if(!ht->lists[i]){
            printf("no ll in lists[%d]\n", i);
        }
        else{
            printf("lists[%d]: \n", i);
            ll_print(ht->lists[i]);
        }
    }
}
