#include "mathlib.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
//#include <stdbool.h>

#define OPTIONS "asctel"

int main(int argc, char **argv){
    int opt = 0;
    while((opt = getopt(argc, argv, OPTIONS) != -1)){
        switch(opt){
        case 'a':
            //bool b_all = true;
            puts("to run all tests");
            break;
        case 's':
            //bool b_sin = true
            puts("to run sin tests");
            
            break;
        case 'c':
            //bool b_cos = true;
            puts("to run cos tests");
            break;
        case 't':
            //bool b_tan = true;
            puts("to run tan tests");
            break;
        case 'e':
            //bool b_exp = true;
            puts("to run exp tests");
            break;
        case 'l':
            //bool b_log = true;
            puts("to run log tests");
            break;
        default:
            fprintf( stderr, "Usage: %s -[asctel]\n", argv[0] );
            }
        }
    return 0;
}

