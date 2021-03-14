#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

TrieNode *trie_node_create(uint16_t code){
    TrieNode *n = (TrieNode *)calloc(1, sizeof(TrieNode));
    for(int i = 0; i < ALPHABET; i++){
        n->children[i] = NULL;
    }
    n->code = code;
    return n;
}

void trie_node_delete(TrieNode *n){
    free(n);
}

TrieNode *trie_create(void){
    TrieNode *root = trie_node_create(1);
    if(root){
        return root;
    }
    return NULL;
}

void trie_reset(TrieNode *root){
    for(int i = 0; i < ALPHABET; i++){
        trie_delete(root->children[i]);
        root->children[i] = NULL;
    }
}

void trie_delete(TrieNode *n){
    if(n != NULL){
        for(int i = 0; i < ALPHABET; i++){
            trie_delete(n->children[i]);
            n->children[i] = NULL;
        }
    }
    trie_node_delete(n);
}

TrieNode *trie_step(TrieNode *n, uint8_t sym){
    if(n->children[sym] != NULL){
        return n->children[sym];
    }
    return NULL;
}

