#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "ll.h"

struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};

Node *node_index(Node *n){
    return n;
}

LinkedList *ll_create(bool mtf){
    LinkedList *ll = malloc(sizeof(LinkedList));
    ll->head = node_create(NULL, NULL);
    ll->tail = node_create(NULL, NULL);
    ll->length = 0;
    ll->head->next = ll->tail;
    ll->tail->prev = ll->head;
    ll->mtf = mtf;
    return ll;
}

void ll_delete(LinkedList **ll){
    Node *index = node_index((*ll)->head);
    while(index != (*ll)->tail){
        node_delete(&index);
        index = node_index(index->next);
    }
    node_delete( &((*ll)->head) );
    free(index);
    free(*ll);
    *ll = NULL;
}

uint32_t ll_length(LinkedList *ll){
    uint32_t len = 0;
    Node *index = node_index(ll->head->next);
    while(index != ll->tail){
        len++;
        index = node_index(index->next);
    }
    free(index);
    ll->length = len;
    return len;
}

void mtf(LinkedList *ll, Node *index){  // move-to-front operation
    index->prev->next = index->next;
    index->next->prev = index->prev;
    index->next = ll->head->next;
    index->prev = ll->head;
    ll->head->next->prev = index;
    ll->head->next = index;
}

Node *ll_lookup(LinkedList *ll, char *oldspeak){
    Node *index = node_index(ll->head->next);
    while(index->oldspeak != oldspeak){
        index = node_index(index->next);
        if(index == ll->tail){
            return NULL;
        }
    }
    if(ll->mtf){
        mtf(ll, index);
    }
    return index;
}


void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak){
    Node *n = node_create(oldspeak, newspeak);
    n->prev = ll->head;
    n->next = ll->head->next;
    ll->head->next->prev = n;
    ll->head->next = n;
}

void ll_print(LinkedList *ll){
    Node *index = node_index(ll->head->next);
    while(index == ll->tail){
        node_print(index);
        index = node_index(index->next);
        printf(" ");
    }
    node_delete(&index);
}

