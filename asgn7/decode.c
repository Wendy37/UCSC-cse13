#include <stdio.h>
#include <stdint.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <math.h>
#include "word.h"
#include "io.h"
#include "code.h"
#include "decode.h"

int bitlen(uint16_t code){
    return log2(code) + 1;
}

int main(void){
    printf("1   ");
    int infile = open("test.txt", O_RDONLY);
    int outfile = open("test2.txt", O_WRONLY);
    FileHeader *header = NULL;
    read_header(infile, header);
    printf("1   ");
    WordTable *wt = wt_create();
    printf("2   ");
    uint8_t curr_sym = 0;
    uint16_t curr_code = 0;
    uint16_t next_code = START_CODE;
    while(read_pair(infile, &curr_code, &curr_sym, bitlen(next_code))){
        printf("3   ");
        wt[next_code] = word_append_sym(wt[curr_code], curr_sym);
        write_word(outfile, wt[next_code]);
        next_code++;
        printf("4   ");
        if(next_code == MAX_CODE){
            wt_reset(wt);
            next_code = START_CODE;
        }
        printf("5   ");
    }
    flush_words(outfile);
    close(infile);
    close(outfile);
    return 0;
}
