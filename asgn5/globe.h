#ifndef globe_h
#define globe_h
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>


#include <stdio.h>

typedef struct globe globe;

globe *g_create(void);

bool swap(uint32_t *A, int64_t a, int64_t b, globe *g);

bool comparison(int64_t a, int64_t b, globe *g);

void print_array(uint32_t *A, uint32_t n);

uint32_t count(globe *g);

uint32_t moves(globe *g);

void delete_g(globe **g);

#endif
