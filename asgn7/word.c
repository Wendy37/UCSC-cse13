#include "word.h"

#include "code.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Word *word_create(uint8_t *syms, uint32_t len) {
    Word *w = (Word *) calloc(1, sizeof(Word));
    w->len = len;
    w->syms = (uint8_t *) calloc(len, sizeof(uint8_t));
    for (uint32_t i = 0; i < len; i++) {
        w->syms[i] = syms[i];
    }
    if (!w) {
        return NULL;
    }
    return w;
}

Word *word_append_sym(Word *w, uint8_t sym) {
    Word *new = word_create(w->syms, w->len);
    if (new->syms == NULL) {
        new->syms = calloc(w->len + 1, sizeof(uint8_t));
    } else {
        new->syms = realloc(new->syms, (w->len + 1) * sizeof(uint8_t));
    }
    new->len = w->len + 1;
    new->syms[w->len] = sym;
    return new;
}

void word_delete(Word *w) {
    free(w->syms);
    w->syms = NULL;
    free(w);
    w = NULL;
}

WordTable *wt_create(void) {
    WordTable *wt = (WordTable *) calloc((MAX_CODE), sizeof(Word *));
    wt[1] = word_create(NULL, 0);
    return wt;
}

void wt_reset(WordTable *wt) {
    for (uint16_t i = 0; i < MAX_CODE; i++) {
        free(wt[i]->syms);
        wt[i]->syms = NULL;
        wt[i] = NULL;
    }
}

void wt_delete(WordTable *wt) {
    for (uint16_t i = 0; i < MAX_CODE; i++) {
        word_delete(wt[i]);
        free(wt[i]);
        wt[i] = NULL;
    }
    free(wt);
    wt = NULL;
}
