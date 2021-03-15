#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <math.h>
#include "io.h"
#include "trie.h"
#include "code.h"

int bitlen(uint16_t code){
    return log2(code) + 1;
}

#define OPTIONS "vi:o:"

int main(int argc, char **argv) {
    int opt = 0;
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    struct stat statbuf;
    fstat(outfile, &statbuf);
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
            case'v':
                break;
            case'i':
                if (optarg != NULL) {
                  infile = open(optarg, O_RDONLY);
                }
                break;
            case'o':
                if (optarg != NULL) {
                  outfile = open(optarg, O_WRONLY|O_CREAT|O_TRUNC, 0600);
                }
                break;
        }
    }
    if(outfile == -1){
        fprintf(stderr, "Failed to open outfile\n");
    }
    FileHeader header;
    header.magic = MAGIC;
    header.protection = statbuf.st_mode;
    fchmod(outfile, header.protection);
    write_header(outfile, &header);
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
