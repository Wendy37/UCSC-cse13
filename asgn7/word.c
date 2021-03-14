#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "word.h"

Word *word_create(uint8_t *syms, uint32_t len){
    Word *w = (Word *)calloc(1, sizeof(Word));
    w->len = len;
    w->syms = (uint8_t *)calloc(len, sizeof(uint8_t));
    for(uint32_t i = 0; i < len; i++){
        w->syms[i] = syms[i];
    }
    if(!w){
        return NULL;
    }
    return w;
}

Word *word_append_sym(Word *w, uint8_t sym){
    Word *new = word_create(w->syms, w->len + 1);
    new->syms[w->len] = sym;
    return new;
}

void word_delete(Word *w){
    free(w->syms);
    w->syms = NULL;
    free(w);
    w = NULL;
}

WordTable *wt_create(void){
    Word **wt = (Word **)calloc((UINT16_MAX - 1), sizeof(Word *));
    wt[1] = word_create(0, 0);
    return wt;
}

void wt_reset(WordTable *wt){
    for(uint16_t i = 0; i < UINT16_MAX - 1; i++){
        wt[i] = NULL;
    }
}

void wt_delete(WordTable *wt){
    for(uint16_t i = 0; i < UINT16_MAX - 1; i++){
        word_delete(wt[i]);
        free(wt[i]);
        wt[i] = NULL;
    }
    free(wt);
    wt = NULL;
}
