#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "set.h"

typedef uint32_t Set; // we can have 32 items

Set set_empty(void){
    return 0;
}

bool set_member(Set s, uint8_t x){
    return s & (1 << x % 8);
}

Set set_insert(Set s, uint8_t x){
    return s | (1 << x % 8);
}

Set set_remove(Set s, uint8_t x){
    return s & ~(1 << x % 8);
}

Set set_intersect(Set s, Set t){
    return s & t;
}

Set set_union(Set s, Set t){
    return s | t;
}

Set set_complement(Set s){
    return ~s;
}

Set set_difference(Set s, Set t){
    return s & ~t;
}
