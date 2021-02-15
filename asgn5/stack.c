#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

struct Stack {
    uint32_t top; // points to the current stack item
    uint32_t capacity; // look as an array length
    int64_t *items; // 8 bytes
};

Stack *stack_create(void) {
    Stack *s = (Stack *) calloc(1, sizeof(Stack *));
    s->top = 0;
    s->capacity = MIN_CAPACITY;
    s->items = (int64_t *) calloc(MIN_CAPACITY, sizeof(int64_t));
    return s;
}

void stack_delete(Stack **s) {
    free((*s)->items);
    free(*s);
}

bool stack_empty(Stack *s) {
    return s->top == 0; // stack is empty
}

bool stack_push(Stack *s, int64_t x) {
    if (s->top == s->capacity) {
        s->capacity *= 2;
        s->items = realloc(s->items, s->capacity * sizeof(int64_t));
        if (!(s->items)) {
            return false;
        } // return false if realloc fails
    }
    s->items[s->top] = x;
    s->top += 1;
    return true; // need to be modified
}

bool stack_pop(Stack *s, int64_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    return true;
}

void stack_print(Stack *s) {
    printf("stack is: \n");
    for (int64_t i = 0; i < s->capacity; i++) {
        printf("%ld ", s->items[i]);
    }
    printf("\n");
    printf("%d\n", s->top);
}
