#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

TrieNode *trie_node_create(uint16_t code){
    TrieNode *n = (TrieNode *)calloc(1, sizeof(TrieNode));
    for(int i = 0; i < 256; i++){
        n->children[i] = NULL;
    }
    n->code = code;
    return n;
}

void trie_node_delete(TrieNode *n){
    for(int i = 0; i < 256; i++){
        free(n->children[i]);
    }
    free(n->children);
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
    
}
