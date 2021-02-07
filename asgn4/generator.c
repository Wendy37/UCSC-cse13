#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include "bm.h"
#include "hamming.h"
#define OPTIONS "i:o:"

uint8_t lower_nibble(uint8_t val){
    return val & 0xF;
}

uint8_t upper_nibble(uint8_t val){
    return val >> 4;
}

int main(int argc, char **argv){
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch(opt){
            case 'i':
                if (optarg != NULL) {
                    infile = fopen(optarg, "rb");
                }
                if (infile == NULL || errno == EINVAL) {
                    fprintf(stderr, "%s is an invalid file.\n", optarg);
                    exit(1);
                }
                break;
            case 'o':
                if (optarg != NULL) {
                    outfile = fopen(optarg, "wb");
                }
                break;
            default: fprintf(stderr, "Usage: %s -[io]\n", argv[0]);
        }
    }
    struct stat statbuf;
    fstat(fileno(infile), &statbuf);
    fchmod(fileno(outfile), statbuf.st_mode);
    
    ham_init();
    uint8_t low = 0;
    uint8_t lowdata = 0;
    uint8_t *lowcode = &low; // code
    uint8_t high = 0;
    uint8_t highdata = 0;
    uint8_t *highcode = &high; // code
    
    while(!feof(infile)){
        //printf("inside while\n");
        int byte = fgetc(infile);
        //printf("byte = %d\n", byte);
        highdata = upper_nibble(byte);
        lowdata = lower_nibble(byte);
        //printf("highdata = %d\n", highdata);
        //printf("lowdata = %d\n", lowdata);

        ham_encode(highdata, highcode);
        ham_encode(lowdata, lowcode);
        
       // printf("highcode = %d\n", high);
        //printf("lowcode = %d\n", low);

        fputc(low, outfile);
        //printf("finish putting low\n");
        fputc(high, outfile);
        //printf("finish putting high\n");

    }
    printf("outside while\n");
    fclose(infile);
    fclose(outfile);
    
    ham_destroy();
    return 0;
}
