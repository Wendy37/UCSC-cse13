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

uint8_t pack_byte(uint8_t upper, uint8_t lower){
    return (upper << 4) | (lower & 0xF);
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
    uint8_t low = 0;  //data
    uint8_t *lowdata = &low;
    uint8_t high = 0; //data
    uint8_t *highdata = &high;
    uint8_t byte;
    int uncor_err = 0;  //uncorrected errors
    int cor_err = 0;    // corrected errors
    int read_bytes = 0;
    double err_rate;
    
    while(!feof(infile)){
        char locode = fgetc(infile);
        read_bytes++;
        ham_rc lownibble = ham_decode(locode, lowdata);
        if (lownibble == HAM_ERR){
            uncor_err++;
        }else if(lownibble == HAM_ERR_OK){
            cor_err++;
        }
        
        if(!feof(infile)){
            char hicode = fgetc(infile);
            read_bytes++;
            ham_rc hinibble = ham_decode(hicode, highdata);
            if (hinibble == HAM_ERR){
                uncor_err++;
            }else if(hinibble == HAM_ERR_OK){
                cor_err++;
            }
        }
        
        byte = pack_byte(high, low);
        fputc(byte, outfile);
    }
    err_rate = uncor_err / read_bytes;

    fprintf(stderr, "Total bytes processed: %d\n", read_bytes);
    fprintf(stderr, "Uncorrected errors: %d\n", uncor_err);
    fprintf(stderr, "Corrected errors: %d\n", cor_err);
    fprintf(stderr, "Error rate: %.6f\n", err_rate);
    fclose(infile);
    fclose(outfile);
    ham_destroy();
    return 0;
}
