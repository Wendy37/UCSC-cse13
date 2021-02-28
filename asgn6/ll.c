#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "node.h"
#include "ll.h"

struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};


LinkedList *ll_create(bool mtf){
    LinkedList *ll = (LinkedList *)calloc(1, sizeof(LinkedList));
    ll->head = node_create(NULL, NULL);
    ll->tail = node_create(NULL, NULL);
    ll->length = 0;
    ll->head->next = ll->tail;
    ll->tail->prev = ll->head;
    ll->mtf = mtf;
    if(!ll){
        return NULL;
    }
    return ll;
}

void ll_delete(LinkedList **ll){
    Node *index = (*ll)->head;
    while(index != (*ll)->tail){
        node_delete(&index);
        index = index->next;
    }
    node_delete( &((*ll)->head) );
    free(index);
    free(*ll);
    *ll = NULL;
}

uint32_t ll_length(LinkedList *ll){
    uint32_t len = 0;
    Node *index = ll->head->next;
    while(index != ll->tail){
        len++;
        index = index->next;
    }
    index=NULL;
    //free(index);
    ll->length = len;
    return ll->length;
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
    if(!ll){
        return NULL;
    }
    Node *index = ll->head->next;
    while(index != ll->tail){
        if (strcmp(oldspeak, index->oldspeak) == 0) {
            if(ll->mtf){
                mtf(ll, index);
            }
            return index;
        }
        else{
            index = index->next;
        }
    }
    return NULL;
}


void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak){
    Node *n = ll_lookup(ll, oldspeak);
    if( !n ){
        Node *n = node_create(oldspeak, newspeak);
        n->prev = ll->head;
        n->next = ll->head->next;
        ll->head->next->prev = n;
        ll->head->next = n;
    }
}

void ll_print(LinkedList *ll){
    Node *index = ll->head->next;
    uint32_t len = ll_length(ll);
    for (uint32_t i = 0; i < len; i++){
        node_print(index);
        index = index->next;
    }
}

