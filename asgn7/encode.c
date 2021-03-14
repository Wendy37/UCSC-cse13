#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <math.h>
#include "io.h"
#include "trie.h"
#include "code.h"
#include "encode.h"

int bitlen(uint16_t code){
    return log2(code) + 1;
}

int main(void) {
    int infile = open("corpora/artificial/alphabet.txt", O_RDONLY);
    int outfile = open("test.txt", O_WRONLY);
    /*FileHeader *header = NULL;
    header->magic = MAGIC;
    write_header(outfile, header);*/
    TrieNode *root = trie_create();
    TrieNode *curr_node = root;
    TrieNode *prev_node = NULL;
    uint8_t curr_sym = 0;
    uint8_t prev_sym = 0;
    uint16_t next_code = START_CODE;
    while(read_sym(infile, &curr_sym)){
        TrieNode *next_node = trie_step(curr_node, curr_sym);
        if(next_node != NULL){
            prev_node = curr_node;
            curr_node = next_node;
        }
        else{
            write_pair(outfile, curr_node->code, curr_sym, bitlen(next_code));
            curr_node->children[curr_sym] = trie_node_create(next_code);
            curr_node = root;
            next_code++;
        }
        if(next_code == MAX_CODE){
            trie_reset(root);
            curr_node = root;
            next_code = START_CODE;
        }
        prev_sym = curr_sym;
    }
    if(curr_node != root){
        write_pair(outfile, prev_node->code, prev_sym, bitlen(next_code));
        next_code = (next_code + 1) % MAX_CODE;
    }
    write_pair(outfile, STOP_CODE, 0, bitlen(next_code));
    flush_pairs(outfile);
    close(infile);
    close(outfile);
    return 0;
}
