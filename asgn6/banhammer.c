#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "parser.h"
#include <regex.h>
#include "hash.h"
#include "banhammer.h"
#include "hash.h"
#include "bf.h"
#include "node.h"

#define OPTIONS "h:f:m"
#define WORD "([a-zA-Z0-9])+(('|-|_)[a-zA-Z0-9]+)*"

int main(int argc, char **argv){
    uint32_t ht_size = 10000;
    uint32_t bf_size = 1 << 21;
    bool mtf = false;
    char temp[1024];
    int opt = 0;
    while( (opt = getopt(argc, argv, OPTIONS)) != -1 ){
        switch (opt){
            case 'h':
                strcpy(temp, optarg);
                sscanf(temp, "%d", &ht_size);
                break;
            case 'f':
                strcpy(temp, optarg);
                sscanf(temp, "%d", &bf_size);
                break;
            case 'm':
                mtf = true;
                break;
            default: fprintf(stderr, "Usage: %s -[h:f:m]\n", argv[0]);
                break;
        }
    }
    
    BloomFilter *bf = bf_create(bf_size);
    HashTable *ht = ht_create(ht_size, mtf);
    
    FILE *infile_bad = fopen("badspeak.txt", "r");
    while( !feof(infile_bad)){
        char *badspeak = (char *)malloc(1024);
        fscanf(infile_bad, "%s\n", badspeak);
        bf_insert(bf, badspeak);
        ht_insert(ht, badspeak, NULL);
    }
    
    FILE *infile_new = fopen("newspeak.txt", "r");
    while( !feof(infile_new)){
        char *oldspeak = (char *)malloc(1024);
        char *newspeak = (char *)malloc(1024);
        fscanf(infile_new, "%s %s\n", oldspeak, newspeak);
        bf_insert(bf, oldspeak);
        ht_insert(ht, oldspeak, newspeak);
    }
    
    char *thoughtcrime[15000];
    char *correction[600];
    uint64_t crimeindex = 0;
    uint64_t corrindex = 0;
    
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }
    char *word = NULL;
    
    
    while ((word = next_word(stdin, &re)) != NULL){
        if(bf_probe(bf, word)){
            Node *n = ht_lookup(ht, word);
            if(n != NULL){
                if(n->newspeak == NULL){
                    
                    thoughtcrime[crimeindex] = n->oldspeak;
                    crimeindex ++;
                }
                else{
                    correction[corrindex] = n->oldspeak;
                    corrindex ++;
                    correction[corrindex] = n->newspeak;
                    corrindex ++;
                }
            }
        }
    }
    
    if(crimeindex != 0){
        printf("Dear Comrade,\n\n");
        printf("You have chosen to use degenerate words that may cause hurt feelings or cause your comrades to think unpleasant thoughts. This is doubleplus bad. To correct your wrongthink and preserve community consensus we will be sending you to joycamp administered by Medellin’s Miniluv. Beware of the hippos.\n\n");
        printf("Your errors: \n\n");
        for(uint64_t i = 0; i < crimeindex; i++){
            printf("%s\n", thoughtcrime[i]);
        }
        
        if(corrindex != 0){
            printf("\nThink of these words on your vacation!\n\n");
            for(uint64_t i = 0; i < corrindex; i += 2){
                printf("%s -> %s\n", correction[i], correction[i+1]);
            }
        }
    }
    else if(corrindex != 0){
        printf("Dear Comrade,\n\n");
        printf("Submitting your text helps to preserve feelings and prevent badthink. Some of the words that you used are not goodspeak. The list shows how to turn the oldspeak words into newspeak.\n\n");
        for(uint64_t i = 0; i < corrindex; i += 2){
            printf("%s -> %s\n", correction[i], correction[i+1]);
        }
    }
    
    clear_words();
    regfree(&re);
    bf_delete(&bf);
    ht_delete(&ht);
    return 0;
}
