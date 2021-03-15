#include "code.h"
#include "io.h"
#include "word.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int bitlen(uint16_t code) {
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
        case 'v': break;
        case 'i':
            if (optarg != NULL) {
                infile = open(optarg, O_RDONLY);
            }
            break;
        case 'o':
            if (optarg != NULL) {
                outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC, 0600);
            }
            break;
        }
    }
    if (outfile == -1) {
        fprintf(stderr, "Failed to open outfile\n");
    }
    FileHeader header;
    read_header(infile, &header);
    if (header.magic != MAGIC) {
        exit(1);
    }
    fchmod(outfile, header.protection);
    WordTable *wt = wt_create();
    uint8_t curr_sym = 0;
    uint16_t curr_code = 0;
    uint16_t next_code = START_CODE;
    while (read_pair(infile, &curr_code, &curr_sym, bitlen(next_code))) {
        wt[next_code] = word_append_sym(wt[curr_code], curr_sym);
        write_word(outfile, wt[next_code]);
        next_code++;
        if (next_code == MAX_CODE) {
            wt_reset(wt);
            next_code = START_CODE;
        }
    }
    flush_words(outfile);
    close(infile);
    close(outfile);
    return 0;
}
