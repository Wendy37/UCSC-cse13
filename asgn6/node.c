#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "node.h"

Node *point(Node *n){   //function returns a pointer to a node
    return n;
}

Node *node_create(char *oldspeak, char *newspeak){
    Node *n = (Node *)calloc(1, sizeof(Node));
    Node *next = (Node *)calloc(1, sizeof(Node));
    Node *prev = (Node *)calloc(1, sizeof(Node));
    n->oldspeak = oldspeak;
    n->newspeak = newspeak;
    n->next = point(next);
    n->prev = point(prev);
    return n;
}

void node_delete(Node **n){
    free((*n)->next);
    free((*n)->prev);
    free(*n);
    *n = NULL;
}

void node_print(Node *n){
    if(n->oldspeak != NULL & n->newspeak != NULL){
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    }
    else if(n->newspeak == NULL & n->oldspeak != NULL){
        printf("%s\n", n->oldspeak);
    }
}
