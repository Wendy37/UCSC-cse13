#include "node.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    char *node_oldspeak = oldspeak;
    char *node_newspeak = newspeak;
    n->oldspeak = node_oldspeak;
    n->newspeak = node_newspeak;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

void node_delete(Node **n) {
    free((*n)->oldspeak);
    free((*n)->newspeak);
    free(*n);
    *n = NULL;
}

void node_print(Node *n) {
    if (n == NULL) {
        printf("the node is NULL\n");
    } else if (n->oldspeak != NULL && n->newspeak != NULL) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    } else if (n->newspeak == NULL && n->oldspeak != NULL) {
        printf("%s\n", n->oldspeak);
    }
}
